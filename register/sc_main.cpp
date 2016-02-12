//------------------------------------------------------------------
// Simple Testbench for 4-bits adder file
// 
// SystemC for VHDL engineers
// (c)www.ht-lab.com
//------------------------------------------------------------------

#include <systemc.h>

#include "stim.h"
#include "register.h"

int sc_main(int argc, char* argv[])
{
    sc_signal<bool> enable, rw, clr;
    sc_signal<sc_uint<5> > addr;
    sc_signal<sc_uint<32> > din, dout;

    sc_clock clk("clk",10,SC_NS,0.5);   // Create a clock signal

    sc_trace_file *fp=sc_create_vcd_trace_file("wave");
    sc_trace(fp, din, "din");
    sc_trace(fp, dout, "dout");
    sc_trace(fp, enable, "enable");
    sc_trace(fp, rw, "rw");
    sc_trace(fp, clr, "clr");
    sc_trace(fp, clk, "clk");
    sc_trace(fp, addr, "addr");

    reg REGISTER("reg");
    REGISTER.clk(clk);
    REGISTER.din(din);
    REGISTER.dout(dout);
    REGISTER.enable(enable);
    REGISTER.rw(rw);
    REGISTER.clr(clr);
    REGISTER.addr(addr);

    stim STIM("stimulus");
    STIM.clk(clk);
    STIM.din(din);
    STIM.dout(dout);
    STIM.enable(enable);
    STIM.rw(rw);
    STIM.clr(clr);
    STIM.addr(addr);

    sc_start(2000, SC_NS);               // Run simulation
    sc_close_vcd_trace_file(fp);

    return 0;                           // Return OK, no errors.
}
