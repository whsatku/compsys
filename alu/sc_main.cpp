//------------------------------------------------------------------
// Simple Testbench for 4-bits adder file
// 
// SystemC for VHDL engineers
// (c)www.ht-lab.com
//------------------------------------------------------------------

#include <systemc.h>

#include "alu.h"
#include "stim.h"
#include "check.h"

int sc_main(int argc, char* argv[])
{
    sc_signal<sc_uint<16> > ain, bin, sum;
    sc_signal<sc_uint<4> > oc;
    sc_signal<bool> co, zflag, oflag;

    sc_clock clk("clk",10,SC_NS,0.5);   // Create a clock signal

    sc_trace_file *fp=sc_create_vcd_trace_file("wave");
    sc_trace(fp, clk, "clock");
    sc_trace(fp, ain, "a_in");
    sc_trace(fp, bin, "b_in");
    sc_trace(fp, sum, "sum");
    sc_trace(fp, co, "carry_out");
    sc_trace(fp, zflag, "zero_flag");
    sc_trace(fp, oflag, "overflow_flag");
    sc_trace(fp, oc, "operation_control");

    alu DUT("alu");                      // Instantiate Device Under Test
    DUT.ain(ain);                       // Connect ports
    DUT.bin(bin);
    DUT.sum(sum);
    DUT.co(co);
    DUT.zflag(zflag);
    DUT.oflag(oflag);
    DUT.oc(oc);

    stim STIM("stimulus");              // Instantiate stimulus generator
    STIM.clk(clk);  
    STIM.ain(ain);
    STIM.bin(bin);
    STIM.oc(oc);

    check CHECK("checker");             // Instantiate checker
    CHECK.clk(clk); 
    CHECK.ain(ain);
    CHECK.bin(bin);
    CHECK.sum(sum);
    CHECK.co(co);
    CHECK.zflag(zflag);
    CHECK.oflag(oflag);
    CHECK.oc(oc);

    sc_start(100, SC_NS);               // Run simulation
    sc_close_vcd_trace_file(fp);

    return 0;                           // Return OK, no errors.
}
