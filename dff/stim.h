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
    sc_out<bool > din;
    sc_in<bool > dout;
    sc_out<bool> enable; // enable =1, to use it
    sc_out<bool> rw; // rw=0 (read), rw=1 (write)
    sc_out<bool> clr; // clr=0; reg is clear to 0; 

    void ps1() {

        // Test when not enabled
        din.write(true);
        wait();
        cout << "Test when not enabled. Expected: 0, got " << dout.read() << endl;

        enable.write(true);
        rw.write(true);
        wait();

        din.write(true);
        wait(); wait(); rw.write(false); wait(); wait();
        cout << "Expected: 1, got " << dout.read() << endl;
        rw.write(true);

        din.write(false);
        wait(); wait(); rw.write(false); wait(); wait();
        cout << "Expected: 0, got " << dout.read() << endl;
        rw.write(true);

        din.write(true);
        wait(); wait(); rw.write(false); wait(); wait();
        cout << "Expected: 1, got " << dout.read() << endl;

        din.write(false);
        rw.write(false);
        wait(); wait();
        cout << "Test ro, Expected: 1, got " << dout.read() << endl;

        clr.write(true);
        rw.write(true);
        wait(); wait(); rw.write(false); wait(); wait();
        cout << "Test clr, Expected: 0, got " << dout.read() << endl;
        clr.write(false);

        sc_stop();                          // End simulation
    }

    SC_CTOR(stim) {  
        SC_THREAD(ps1);                     // Run ps1 only ones
        sensitive << clk.pos();
    }
};
#endif

