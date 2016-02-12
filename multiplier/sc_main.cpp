//------------------------------------------------------------------
// Simple Testbench for 4-bits adder file
// 
// SystemC for VHDL engineers
// (c)www.ht-lab.com
//------------------------------------------------------------------

#include <systemc.h>

sc_trace_file *fp=sc_create_vcd_trace_file("wave");

#include "multiplier.h"
#include "stim.h"
#include "check.h"

int sc_main(int argc, char* argv[])
{
    sc_signal<sc_uint<8> > ain, bin, ra, rb;
    sc_signal<sc_uint<16> > result ,rc;
    sc_signal<bool> ready, start;

    sc_clock clk("clk",10,SC_NS,0.5);   // Create a clock signal

    sc_trace(fp, clk, "clk");
    sc_trace(fp, ain, "A");
    sc_trace(fp, bin, "B");
    sc_trace(fp, result, "C");

    sc_trace(fp, ra, "RA");
    sc_trace(fp, rb, "RB");
    sc_trace(fp, rc, "RC");
    sc_trace(fp, ready, "Ready");
    sc_trace(fp, start, "Start");

    multiplier DUT("multiplier");                      // Instantiate Device Under Test
    DUT.ain(ain);
    DUT.bin(bin);
    DUT.ra(ra);
    DUT.rb(rb);
    DUT.rc(rc);
    DUT.ready(ready);
    DUT.start(start);
    DUT.result(result);
    DUT.clk(clk);

    stim STIM("stimulus");              // Instantiate stimulus generator
    STIM.clk(clk);  
    STIM.ain(ain);
    STIM.bin(bin);
    STIM.ready(ready);
    STIM.start(start);

    check CHECK("check");
    CHECK.clk(clk);
    CHECK.ain(ain);
    CHECK.bin(bin);
    CHECK.ready(ready);
    CHECK.result(result);

    sc_start(150, SC_NS);               // Run simulation
    sc_close_vcd_trace_file(fp);

    return 0;                           // Return OK, no errors.
}
