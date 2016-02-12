#ifndef REGISTER_H
#define REGISTER_H

#include <systemc.h>
#include "dff.h"
                                
SC_MODULE(reg) {
    sc_in<bool > clk;
    sc_in<sc_uint<32> > din;
    sc_out<sc_uint<32> > dout;
    sc_in<bool> enable; // enable =1, to use it
    sc_in<bool> rw; // rw=0 (read), rw=1 (write)
    sc_in<bool> clr; // clr=0; reg is clear to 0; 
    sc_in<sc_uint<5> > addr;

    dff* registers[32][32];
    sc_signal<bool>* in_signals[32][32]; // read here to read from registers
    sc_signal<bool>* out_signals[32][32]; // write here to write to registers


    void p1() {
        while(true){
            if(!enable.read()){
                wait();
                continue;
            }

            if(rw){
                sc_uint<32> input = din.read();

                for(int i = 0; i < 32; i++){
                    out_signals[addr.read()][i]->write(input[i]);
                }
            }else{
                sc_uint<32> out;

                // cout << "attempting read from " << addr.read() << endl;

                for(int i = 0; i < 32; i++){
                    out[i] = in_signals[addr.read()][i]->read();
                }

                dout.write(out);
            }

            wait();
        }
    }


    SC_CTOR(reg) {
        using namespace std;
        sc_uint<32> init_val[32];

        ifstream fin;
        fin.open("init.reg", ifstream::in);

        while(!fin.eof()){
            string no, val;
            fin >> no >> val;
            
            if(no.length() == 0){
                continue;
            }

            int index = atoi(no.c_str());
            int value = atoi(val.c_str());
            
            init_val[index] = value;
        }

        for(int i = 0; i < 32; i++){
            for(int j = 0; j < 32; j++){
                char* name = (char*) malloc(sizeof(char) * 12);
                sprintf(name, "dff[%d][%d]", i, j);

                in_signals[i][j] = new sc_signal<bool>;
                out_signals[i][j] = new sc_signal<bool>;

                registers[i][j] = new dff(name);
                registers[i][j]->clk(clk);
                registers[i][j]->enable(enable);
                registers[i][j]->din(*out_signals[i][j]);
                registers[i][j]->dout(*in_signals[i][j]);
                registers[i][j]->rw(rw);
                registers[i][j]->clr(clr);
                registers[i][j]->value = init_val[i][j];
            }
        }

        SC_CTHREAD(p1,clk.pos());
    }
};
#endif

