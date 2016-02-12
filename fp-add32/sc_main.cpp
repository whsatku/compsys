//------------------------------------------------------------------
// Simple Testbench for 4-bits adder file
// 
// SystemC for VHDL engineers
// (c)www.ht-lab.com
//------------------------------------------------------------------

#include <systemc.h>

#include "fp-add32.h"
#include "stim.h"
#include "check.h"

int sc_main(int argc, char* argv[])
{
    sc_signal<float> a, b;
    sc_signal<sc_dt::scfx_ieee_float > output;
    sc_signal<bool> oflag, uflag;

    sc_clock clk("clk",10,SC_NS,0.5);   // Create a clock signal

    // sc_trace_file *fp=sc_create_vcd_trace_file("wave");
    // sc_trace(fp, output, "output");
    // sc_trace(fp, oflag, "oflag");
    // sc_trace(fp, uflag, "uflag");
    // sc_trace(fp, a, "a");
    // sc_trace(fp, b, "b");

    fp_add32 DUT("fp_add32");
    DUT.a(a);
    DUT.b(b);
    DUT.c(output);
    DUT.oflag(oflag);
    DUT.uflag(uflag);

    stim STIM("stimulus");
    STIM.clk(clk);  
    STIM.a(a);
    STIM.b(b);

    check CHECK("checker");             // Instantiate checker
    CHECK.clk(clk); 
    CHECK.a(a);
    CHECK.b(b);
    CHECK.output(output);

    sc_start(100, SC_NS);               // Run simulation
    // sc_close_vcd_trace_file(fp);

    return 0;                           // Return OK, no errors.
}
