//------------------------------------------------------------------
// Simple Testbench for 4-bits adder file
// 
// SystemC for VHDL engineers
// (c)www.ht-lab.com
//------------------------------------------------------------------

#include <systemc.h>

#include "lcm.h"
#include "tb.h"

int sc_main(int argc, char* argv[])
{

    tb_lcm TB("tb");

    sc_start(5000, SC_NS);

    return 0;                           // Return OK, no errors.
}
