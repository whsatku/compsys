//------------------------------------------------------------------
// Simple 4-bits adder
// 
// SystemC for VHDL engineers
// (c)www.ht-lab.com
//------------------------------------------------------------------
#ifndef STIM_H
#define STIM_H

#include <systemc.h>
#include <alu.h>
                                
SC_MODULE(stim) {
    sc_in<bool> clk;
    sc_out<sc_uint<5> > s1, s2, s3;
    sc_out<sc_uint<16> > write;
    sc_out<bool> rw;
    sc_in<sc_uint<16> > result;
    sc_out<sc_uint<4> > operation;

    void ps1() {
        // Create the test bench where $S1=3, $S2=7 and ALU control is ADD. We want to perform $S3=$S2+$S1.
        operation.write(ALU_ADD);
        s1.write(3);
        s2.write(7);

        wait(); wait(); wait();
        cout << "add result is " << result.read() << "\t" << result.read().to_string(SC_BIN) << endl;

        // Next feed another set of inputs:  for ALU control as AND to perform $S1=7, $S3= 12,  $S2 = $S1 AND $S3
        operation.write(ALU_AND);
        s1.write(7);
        s2.write(12);

        wait(); wait(); wait();
        cout << "and result is " << result.read() << " \t" << result.read().to_string(SC_BIN) << endl;
        sc_stop();
    }

    SC_CTOR(stim) {  
        SC_THREAD(ps1);                     // Run ps1 only ones
        sensitive << clk.pos();
    }
};
#endif

