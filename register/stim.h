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
    sc_in<bool > clk;
    sc_out<sc_uint<32> > din;
    sc_in<sc_uint<32> > dout;
    sc_out<bool> enable; // enable =1, to use it
    sc_out<bool> rw; // rw=0 (read), rw=1 (write)
    sc_out<bool> clr; // clr=0; reg is clear to 0; 
    sc_out<sc_uint<5> > addr;

    void ps1() {

        // Test when not enabled
        din.write(true);
        wait();
        cout << "Test when not enabled. Expected: 0, got " << dout.read() << endl;

        enable.write(true);
        wait();

        // Test initial loading
        // use gen_init.py to generate test data

        for(int i=0; i < 32; i++){
            addr.write(i);
            wait(); wait(); wait();
            cout << "Data load, Expected: " << i << ", got " << dout.read() << endl;
        }

        addr.write(0);
        rw.write(true);
        din.write(3);
        wait(); wait(); rw.write(false); wait(); wait(); wait();
        cout << "Expected: binary 3, got " << dout.read().to_string(SC_BIN) << endl;
        rw.write(true);

        din.write(false);
        rw.write(false);
        wait(); wait(); wait();
        cout << "Test ro, Expected: 1, got " << dout.read() << endl;

        clr.write(true);
        rw.write(true);
        wait(); wait(); rw.write(false); wait(); wait(); wait();
        cout << "Test clr, Expected: 0, got " << dout.read() << endl;
        clr.write(false);
        rw.write(true);

        din.write(3);
        wait(); wait(); rw.write(false); wait(); wait(); wait();
        cout << "addr 0, Expected: 3, got " << dout.read() << endl;
        rw.write(true);

        addr.write(31);
        din.write(4294967295);
        wait(); wait(); rw.write(false); wait(); wait(); wait();
        cout << "addr 31, Expected: binary 4294967295, got " << dout.read().to_string(SC_BIN) << endl;

        addr.write(0);
        wait(); wait(); wait();
        cout << "addr 0, Expected: 3, got " << dout.read() << endl;


        sc_stop();                          // End simulation
    }

    SC_CTOR(stim) {  
        SC_THREAD(ps1);                     // Run ps1 only ones
        sensitive << clk.pos();
    }
};
#endif

