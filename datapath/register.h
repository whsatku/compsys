#ifndef REGISTER_H
#define REGISTER_H

#include <systemc.h>
#include "dff.h"

#define REG_COUNT 16
#define REG_WIDTH 16
                                
SC_MODULE(reg) {
    sc_in<bool > clk;
    sc_in<sc_uint<REG_WIDTH> > din;
    sc_out<sc_uint<REG_WIDTH> > s1_d, s2_d;
    sc_in<bool> rw; // rw=0 (read), rw=1 (write)
    sc_in<bool> clr; // clr=0; reg is clear to 0; 
    sc_in<sc_uint<5> > addr1, addr2;

    dff* registers[REG_COUNT][REG_WIDTH];
    sc_signal<bool>* in_signals[REG_COUNT][REG_WIDTH]; // read here to read from registers
    sc_signal<bool>* out_signals[REG_COUNT][REG_WIDTH]; // write here to write to registers


    void p1() {
        while(true){
            if(rw){
                sc_uint<REG_WIDTH> input = din.read();

                for(int i = 0; i < REG_WIDTH; i++){
                    out_signals[addr1.read()][i]->write(input[i]);
                }
            }else{
                sc_uint<REG_WIDTH> out;

                for(int i = 0; i < REG_WIDTH; i++){
                    out[i] = in_signals[addr1.read()][i]->read();
                }

                s1_d.write(out);

                for(int i = 0; i < REG_WIDTH; i++){
                    out[i] = in_signals[addr2.read()][i]->read();
                }

                s2_d.write(out);
            }
            wait();
        }
    }


    SC_CTOR(reg) {
        using namespace std;
        sc_uint<REG_COUNT> init_val[REG_COUNT];

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

            if(index >= REG_COUNT){
                cout << "Invalid address " << index << endl;
                continue;
            }
            
            init_val[index] = value;
        }

        for(int i = 0; i < REG_COUNT; i++){
            for(int j = 0; j < REG_WIDTH; j++){
                char* name = (char*) malloc(sizeof(char) * 12);
                sprintf(name, "dff[%d][%d]", i, j);

                in_signals[i][j] = new sc_signal<bool>;
                out_signals[i][j] = new sc_signal<bool>;

                registers[i][j] = new dff(name);
                registers[i][j]->clk(clk);
                registers[i][j]->din(*out_signals[i][j]);
                registers[i][j]->dout(*in_signals[i][j]);
                registers[i][j]->rw(rw);
                registers[i][j]->clr(clr);
                registers[i][j]->i_value = init_val[i][j];
            }
        }

        SC_CTHREAD(p1,clk.pos());
    }
};
#endif

