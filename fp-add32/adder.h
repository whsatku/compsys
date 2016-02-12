#ifndef ADDER_H
#define ADDER_H
// stolen from systemc
#define SCFX_MASK_(Size) ((1u << (Size))-1u)
#define ADDER_DEBUG 0

#include <systemc.h>

using namespace sc_dt;
                                
SC_MODULE(adder) {
    sc_in<scfx_ieee_float> a, b;
    sc_out<scfx_ieee_float> c;
    sc_out<bool> oflag, uflag;

    void p1() { 
        // c.write(scfx_ieee_float((float) a.read() + (float) b.read()));
        
        // clone
        scfx_ieee_float out = scfx_ieee_float();

        int expo = max(a.read().exponent(), b.read().exponent());
        unsigned long m1 = adjust_exp(a.read(), expo);
        unsigned long m2 = adjust_exp(b.read(), expo);

        if(ADDER_DEBUG){
            cout << sc_int<8>(b.read().exponent() + SCFX_IEEE_FLOAT_BIAS).to_string(SC_BIN) << "\t";
            cout << sc_int<SCFX_IEEE_FLOAT_M_SIZE>(b.read().mantissa()).to_string(SC_BIN) << endl;
            cout << sc_int<8>(expo).to_string(SC_BIN) << "\t";
            cout << sc_int<SCFX_IEEE_FLOAT_M_SIZE>(m2).to_string(SC_BIN) << endl;
        }

        unsigned long outm = m1+m2;
        // shift_under(&outm, &expo);

        if(ADDER_DEBUG){
            cout << "out\t" << sc_int<8>(expo).to_string(SC_BIN) << "\t";
            cout << sc_int<SCFX_IEEE_FLOAT_M_SIZE>(outm).to_string(SC_BIN) << " " << expo << endl;

            scfx_ieee_float expected = scfx_ieee_float((float) a.read() + (float) b.read());
            cout << "exp\t" << sc_int<8>(expected.exponent()).to_string(SC_BIN) << "\t";
            cout << sc_int<SCFX_IEEE_FLOAT_M_SIZE>(expected.mantissa()).to_string(SC_BIN) << endl;
        }

        out.exponent(expo);
        out.mantissa(outm);

        if(ADDER_DEBUG){
            cout << "outr\t" << sc_int<8>(out.exponent()).to_string(SC_BIN) << "\t";
            cout << sc_int<SCFX_IEEE_FLOAT_M_SIZE>(out.mantissa()).to_string(SC_BIN) << endl;
        }

        c.write(out);
        
    }

    int max(int a, int b){
        return a > b ? a : b;
    }

    unsigned long adjust_exp(scfx_ieee_float num, int expo){
        unsigned long out = num.mantissa();
        int cur = num.exponent();
        // add the hidden bit
        out |= 1 << (SCFX_IEEE_FLOAT_M_SIZE);
        while(cur < expo){
            out >>= 1;
            cur++;
        }
        return out;
    }

    void shift_under(unsigned long* num, int* expo){
        // remove bits until under the maximum mantissa
        while(*num > SCFX_MASK_(SCFX_IEEE_FLOAT_M_SIZE+1)){
            if(ADDER_DEBUG){
                cout << "shift " << sc_int<CHAR_BIT*sizeof(long)>(*num).to_string(SC_BIN) << endl;
            }
            *num >>= 1;
            *expo += 1;
        }
        *num &= SCFX_MASK_(SCFX_IEEE_FLOAT_M_SIZE);
    }

    SC_CTOR(adder) {     
        SC_METHOD(p1);  
        sensitive << a << b; 
    }
};
#endif

