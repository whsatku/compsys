//------------------------------------------------------------------
// Simple 4-bits adder
// 
// SystemC for VHDL engineers
// (c)www.ht-lab.com
//------------------------------------------------------------------
#ifndef STIM_H
#define STIM_H

#include <systemc.h>
                                
SC_MODULE(stim) {
    sc_in<bool> clk, ready;
    sc_out<sc_uint<8> > ain, bin;
    sc_out<bool> start;

    void wait_dev(){
        bool has_wait;
        start.write(true);
        while(ready.read() || !has_wait){
            has_wait=true;
            wait();
        }
        start.write(false);
        wait();
        while(!ready.read()){
            wait();
        }
    }

    void ps1() {    

        ain.write("0b0000");
        bin.write("0b0000");
        wait_dev();

        ain.write(6);
        bin.write(7);
        wait_dev();

        ain.write(11);
        bin.write(4000000);
        wait_dev();

        sc_stop();                          // End simulation
    }

    SC_CTOR(stim) {  
        SC_THREAD(ps1);                     // Run ps1 only ones
        sensitive << clk.pos();
    }
};
#endif

