//------------------------------------------------------------------
// Simple Testbench for 4-bits adder file
// 
// SystemC for VHDL engineers
// (c)www.ht-lab.com
//------------------------------------------------------------------

#include <systemc.h>

#include "dff.h"
#include "stim.h"

int sc_main(int argc, char* argv[])
{
    sc_signal<bool> din, dout, enable, rw, clr;

    sc_clock clk("clk",10,SC_NS,0.5);   // Create a clock signal

    sc_trace_file *fp=sc_create_vcd_trace_file("wave");
    sc_trace(fp, din, "din");
    sc_trace(fp, dout, "dout");
    sc_trace(fp, enable, "enable");
    sc_trace(fp, rw, "rw");
    sc_trace(fp, clr, "clr");
    sc_trace(fp, clk, "clk");

    dff DUT("dff");
    DUT.clk(clk);
    DUT.din(din);
    DUT.dout(dout);
    DUT.enable(enable);
    DUT.rw(rw);
    DUT.clr(clr);

    stim STIM("stimulus");
    STIM.clk(clk);
    STIM.din(din);
    STIM.dout(dout);
    STIM.enable(enable);
    STIM.rw(rw);
    STIM.clr(clr);

    sc_start(500, SC_NS);               // Run simulation
    sc_close_vcd_trace_file(fp);

    return 0;                           // Return OK, no errors.
}
