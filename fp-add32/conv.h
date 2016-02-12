#ifndef CONV_H
#define CONV_H

#include <systemc.h>
                                
SC_MODULE(conv) {
    sc_in<float> input;
    sc_out<sc_dt::scfx_ieee_float > output;

    void p1() { 
        output.write(sc_dt::scfx_ieee_float(input.read()));
    }

    SC_CTOR(conv) {     
        SC_METHOD(p1);  
        sensitive << input;
    }
};
#endif