//------------------------------------------------------------------
// 4-bits adder checker module
// 
// SystemC for VHDL engineers
// (c)www.ht-lab.com
//------------------------------------------------------------------
#ifndef CHECK_H
#define CHECK_H

#include <systemc.h>

#include <iostream>
using namespace std;       
                                
SC_MODULE(check) {
    sc_in<bool> clk, ready;
    sc_in<sc_uint<8> > ain, bin;
    sc_in<sc_uint<16> > result;

    void pc1() {    
        cout << "result:" << endl;
        cout << "a in: " << ain.read() << endl;
        cout << "b in: " << bin.read() << endl;
        cout << "result: " << result.read() << endl;
        cout << "expected: " << ain.read() * bin.read() << endl;
        cout << endl;
    }

    SC_CTOR(check) {     
        SC_METHOD(pc1);                     
        sensitive << ready.pos();
        dont_initialize();
    }
};
#endif

