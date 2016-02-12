//------------------------------------------------------------------
// Simple 4-bits adder
// 
// SystemC for VHDL engineers
// (c)www.ht-lab.com
//------------------------------------------------------------------
#ifndef DEVICE_H
#define DEVICE_H

#include <systemc.h>
#define ALU_ADD 0
#define ALU_SUB 1
#define ALU_XOR 2
#define ALU_AND 3
#define ALU_OR 4
#define ALU_NOT 5
#define ALU_STL 6
                                
SC_MODULE(multiplier) {
    sc_in<bool> clk, start;
    sc_in<sc_uint<8> > ain, bin;
    sc_out<sc_uint<16> > result;
    sc_out<bool> ready;

    // debug signals
    sc_out<sc_uint<8> > ra, rb;
    sc_out<sc_uint<16> > rc;

    void p1() {
        while(true){
            while(!start.read()){
                wait();
            }

            sc_uint<8> ra_d, rb_d;
            sc_uint<16> rc_d;

            ra_d = ain.read();
            rb_d = bin.read();
            rc_d = 0;

            ready.write(false);

            ra.write(ra_d);
            rb.write(rb_d);
            rc.write(rc_d);
            wait();

            cout << "Mult in " << ra_d.to_string(SC_BIN) << " " << rb_d.to_string(SC_BIN) << endl;

            while(ra_d > 0){
                if(ra_d[0] == 1){
                    rc_d = rc_d + rb_d;
                }
                ra_d = ra_d >> 1;
                rb_d = rb_d << 1;
                cout << "Mult step " << ra_d.to_string(SC_BIN) << " " << rb_d.to_string(SC_BIN) << " " << rc_d.to_string(SC_BIN) << endl;
                ra.write(ra_d);
                rb.write(rb_d);
                rc.write(rc_d);
                wait();
            }

            result.write(rc_d);
            ready.write(true);
        }
    }

    SC_CTOR(multiplier) {     
        SC_CTHREAD(p1, clk.pos());
    }
};
#endif

