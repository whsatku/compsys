//------------------------------------------------------------------
// Simple 4-bits adder
// 
// SystemC for VHDL engineers
// (c)www.ht-lab.com
//------------------------------------------------------------------
#ifndef ALU_H
#define ALU_H

#include <systemc.h>
#define ALU_ADD 0
#define ALU_SUB 1
#define ALU_XOR 2
#define ALU_AND 3
#define ALU_OR 4
#define ALU_NOT 5
#define ALU_STL 6
                                
SC_MODULE(alu) {
    sc_in<sc_uint<16> > ain, bin;
    sc_out<sc_uint<16> > sum;
    sc_out<bool> co;
    // operation control
    // 0 - add
    // 1 - sub
    // 2 - xor
    // 3 - and
    // 4 - or
    // 5 - not
    // 6 - set less than
    sc_in<sc_uint<4> > oc;

    sc_out<bool> zflag, oflag;

    sc_uint<16> sum_s;

    // 1-bit ripple carry fulladder, note the cof reference bool&
    bool fulladder(bool a, bool b, bool cif, bool& cof) {
        bool sumr;
        sumr =(a ^ b) ^ cif;
        cof=(a & b) | ((a ^ b) & cif);          
        return sumr;    
    }

    void p1() { 
        sc_uint<16> b2c;
        bool out;
        switch(oc.read()){
            case ALU_ADD:
                adder(ain.read(), bin.read());
                break;
            case ALU_SUB:
                b2c = bin.read();
                b2c[15] = 0;
                b2c = ~b2c;
                b2c = adder(b2c, 1);
                adder(ain.read(), b2c);
                oflag.write(false);
                break;
            case ALU_XOR:
                sum.write(ain.read() ^ bin.read());
                break;
            case ALU_AND:
                sum.write(ain.read() & bin.read());
                break;
            case ALU_OR:
                sum.write(ain.read() | bin.read());
                break;
            case ALU_NOT:
                sum.write(~(ain.read()));
                break;
            case ALU_STL:
                out = false;
                // 1011 < 1101
                for(int i = 0; i < 16; i++){
                    bool a = ain.read()[i];
                    bool b = bin.read()[i];
                    // a != b
                    out |= ((a && !b) || (!a && b)) && (a && !b);
                }
                sum.write(!out);
                break;
        }
    }

    sc_uint<16> adder(sc_uint<16> a, sc_uint<16> b){
        bool zero = false;
        bool carry = false;

        for(int i = 0; i < 16; i++){
            sum_s[i]=fulladder(a[i],b[i], carry, carry);
            zero |= sum_s[i];
        }
        zero |= carry;

        sum.write(sum_s);

        zflag.write(!zero);
        oflag.write(carry);
        return sum_s;
    }

    SC_CTOR(alu) {     
        SC_METHOD(p1);  
        sensitive << ain << bin << oc;
    }
};
#endif

