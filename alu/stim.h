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
    sc_in<bool> clk;
    sc_out<sc_uint<16> > ain, bin;
    sc_out<sc_uint<4> > oc;

    void ps1() {    

        ain.write("0b0000");
        bin.write("0b0000");
        oc.write(0);
        wait();

        for(int i = 0; i <= 6; i++){
            ain.write("0b0000000000000100");
            bin.write("0b0000000000000011");
            oc.write(i);
            wait();
        }

        sc_stop();                          // End simulation
    }

    SC_CTOR(stim) {  
        SC_THREAD(ps1);                     // Run ps1 only ones
        sensitive << clk.pos();
    }
};
#endif

