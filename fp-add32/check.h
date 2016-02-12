//------------------------------------------------------------------
// 4-bits adder checker module
// 
// SystemC for VHDL engineers
// (c)www.ht-lab.com
//------------------------------------------------------------------
#ifndef CHECK_H
#define CHECK_H

#include <systemc.h>     
                                
SC_MODULE(check) {
    sc_in<sc_dt::scfx_ieee_float > output;
    sc_in<float> a, b;
    sc_in<bool> clk;

    void pc1() {    

        cout << a.read() << " + " << b.read() << " output " << (float) output.read() << endl;

    }

    SC_CTOR(check) {     
        SC_METHOD(pc1);                     
        sensitive << output;
        dont_initialize();
    }
};
#endif

