//------------------------------------------------------------------
// Simple Testbench for 4-bits adder file
// 
// SystemC for VHDL engineers
// (c)www.ht-lab.com
//------------------------------------------------------------------

#include <systemc.h>

#include "alu.h"
#include "stim.h"
#include "register.h"

int sc_main(int argc, char* argv[])
{
    sc_signal<sc_uint<5> > s1, s2, s3;
    sc_signal<sc_uint<16> > s1_d, s2_d, write;
    sc_signal<bool> zflag, oflag, rw, clr, co;
    sc_signal<sc_uint<16> > result;
    sc_signal<sc_uint<4> > operation;

    sc_clock clk("clk",10,SC_NS,0.5);   // Create a clock signal

    sc_trace_file *fp=sc_create_vcd_trace_file("wave");
    sc_trace(fp, s1, "s1");
    sc_trace(fp, s2, "s2");
    sc_trace(fp, s3, "s3");
    sc_trace(fp, write, "write");
    sc_trace(fp, s1_d, "s1_d");
    sc_trace(fp, s2_d, "s2_d");
    sc_trace(fp, zflag, "zflag");
    sc_trace(fp, oflag, "oflag");
    sc_trace(fp, result, "result");
    sc_trace(fp, operation, "operation");
    sc_trace(fp, clk, "clk");

    reg REGISTER("reg");
    REGISTER.clk(clk);
    REGISTER.din(write);
    REGISTER.s1_d(s1_d);
    REGISTER.s2_d(s2_d);
    REGISTER.rw(rw);
    REGISTER.clr(clr);
    REGISTER.addr1(s1);
    REGISTER.addr2(s2);

    alu ALU("alu");
    ALU.ain(s1_d);
    ALU.bin(s2_d);
    ALU.sum(result);
    ALU.co(co);
    ALU.oc(operation);
    ALU.zflag(zflag);
    ALU.oflag(oflag);

    stim STIM("stimulus");
    STIM.clk(clk);
    STIM.s1(s1);
    STIM.s2(s2);
    STIM.s3(s3);
    STIM.write(write);
    STIM.rw(rw);
    STIM.result(result);
    STIM.operation(operation);

    sc_start(2000, SC_NS);               // Run simulation
    sc_close_vcd_trace_file(fp);

    return 0;                           // Return OK, no errors.
}
