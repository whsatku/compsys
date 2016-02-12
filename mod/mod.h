#ifndef MOD_H
#define MOD_H

#include <systemc.h>

#define MOD_WIDTH 16

SC_MODULE(mod) {

	sc_in<bool> clk, reset, go_i;
	sc_in<sc_uint<MOD_WIDTH> > x_i, y_i;
	sc_out<bool> done_o;
	sc_out<sc_uint<MOD_WIDTH> > r_o;

	void p1() {
		if(!go_i.read()){
			done_o.write(false);
			return;
		}
		int x = x_i.read();
		int y = y_i.read();
		if(y == 0){
			r_o.write(0);
		}else{
			r_o.write(x%y);
		}
		done_o.write(true);
	}

	SC_CTOR(mod) {
		SC_METHOD(p1);  
		sensitive << clk.pos() << x_i << y_i;
		reset_signal_is(reset, true);
	}
};
#endif

