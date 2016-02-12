#ifndef FP_ADD
#define FP_ADD

#include <systemc.h>
#include <conv.h>
#include <adder.h>
                                
SC_MODULE(fp_add32) {
    sc_in<float> a, b;
    sc_signal<sc_dt::scfx_ieee_float > a_fp, b_fp;
    sc_out<sc_dt::scfx_ieee_float > c;
    sc_out<bool> oflag, uflag;

    conv* conv1;
    conv* conv2;
    adder* addr;

    SC_CTOR(fp_add32) {     
    	conv1 = new conv("conv1");
        conv1->input(a);
        conv1->output(a_fp);

        conv2 = new conv("conv2");
        conv2->input(b);
        conv2->output(b_fp);

        addr = new adder("adder");
        addr->a(a_fp);
        addr->b(b_fp);
        addr->c(c);
        addr->oflag(oflag);
        addr->uflag(uflag);
    }
};
#endif