#ifndef DFF_H
#define DFF_H

#include <systemc.h>
                                
SC_MODULE(dff) {
    sc_in<bool > clk;
    sc_in<bool > din;
    sc_out<bool > dout;
    sc_in<bool> rw; // rw=0 (read), rw=1 (write)
    sc_in<bool> clr; // clr=0; reg is clear to 0;

    bool i_value = false; 

    void p1() {
        bool value = i_value;
        while(true){
            if(rw.read()){
                value = din.read();
            }else{
                dout.write(value);
            }

            wait();
        }
    }


    SC_CTOR(dff) {
        SC_CTHREAD(p1,clk.pos());
        reset_signal_is(clr, true);
    }
};
#endif

