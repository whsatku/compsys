//------------------------------------------------------------------
// 4-bits adder checker module
// 
// SystemC for VHDL engineers
// (c)www.ht-lab.com
//------------------------------------------------------------------
#ifndef CHECK_H
#define CHECK_H

#include <systemc.h>

#include <iostream>
using namespace std;       
                                
SC_MODULE(check) {
    sc_in<bool> clk;
    sc_in<sc_uint<16> > ain, bin;
    sc_in<sc_uint<16> > sum;
    sc_in<bool> co, zflag, oflag;
    // operation control
    // 0 - add
    // 1 - sub
    // 2 - xor
    // 3 - and
    // 4 - or
    // 5 - not
    // 6 - set less than
    sc_in<sc_uint<4> > oc;

    sc_uint<17> sumc;
    sc_uint<16> expected;

    void pc1() {    

        switch(oc.read()){
            case 0:
                sumc=ain.read() + bin.read();

                cout << "alu " << ain.read() << " + " << bin.read() << " =" << sum.read()+co.read()*16; 
                if (sumc(14,0)==sum.read() && co==sumc[15]) {
                    cout << " Passed" << endl;
                } else {
                    cout << " Failed, expected sum=" << sumc(14,0) << " co=" << sumc[15] << endl;
                }
                if (zflag.read()==true) {
                    cout << "zero value" << endl;
                }
                if (oflag.read()==true) {
                    cout << "overflow value" << endl;
                }
                break;
            case 1:
                sumc=ain.read() - bin.read();

                cout << "alu " << ain.read() << " - " << bin.read() << " =" << sum.read()+co.read()*16; 
                if (sumc(14,0)==sum.read() && co==sumc[15]) {
                    cout << " Passed" << endl;
                } else {
                    cout << " Failed, expected sum=" << sumc(14,0) << " co=" << sumc[15] << " got " << sum.read().to_string(SC_BIN) << endl;
                }
                if (zflag.read()==true) {
                    cout << "zero value" << endl;
                }
                if (oflag.read()==true) {
                    cout << "overflow value" << endl;
                }
                break;
            case 2:
                cout << "alu " << ain.read() << " xor " << bin.read() << " =" << sum.read();
                expected = ain.read() ^ bin.read();
                if(expected == sum.read()){
                    cout << " Passed" << endl;
                }else{
                    cout << " Failed. Expected " << expected << " got " << sum.read() << endl;
                }
                break;
            case 3:
                cout << "alu " << ain.read() << " and " << bin.read() << " =" << sum.read();
                expected = ain.read() & bin.read();
                if(expected == sum.read()){
                    cout << " Passed" << endl;
                }else{
                    cout << " Failed. Expected " << expected << " got " << sum.read() << endl;
                }
                break;
            case 4:
                cout << "alu " << ain.read() << " or " << bin.read() << " =" << sum.read();
                expected = ain.read() | bin.read();
                if(expected == sum.read()){
                    cout << " Passed" << endl;
                }else{
                    cout << " Failed. Expected " << expected << " got " << sum.read() << endl;
                }
                break;
            case 5:
                cout << "alu not " << ain.read() << " =" << sum.read();
                expected = ~(ain.read());
                if(expected == sum.read()){
                    cout << " Passed" << endl;
                }else{
                    cout << " Failed. Expected " << expected << " got " << sum.read() << endl;
                }
                break;
            case 6:
                cout << "alu stl " << ain.read() << ", " << bin.read() << " =" << sum.read();
                if(ain.read() < bin.read() && sum.read() == 1){
                    cout << " Passed" << endl;
                }else if(ain.read() >= bin.read() && sum.read() == 0){
                    cout << " Passed" << endl;
                }else{
                    cout << " Failed.";
                }
                break;
        }

    }

    SC_CTOR(check) {     
        SC_METHOD(pc1);                     
        sensitive << clk.pos();
        dont_initialize();
    }
};
#endif

