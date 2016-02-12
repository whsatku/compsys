#ifndef LCM_H
#define LCM_H

#include <systemc.h>
#include <numeric>

#define LCM_WIDTH 16

SC_MODULE(lcm) {

	sc_in<bool> clk, reset, go_i;
	sc_in<sc_uint<LCM_WIDTH> > x_i, y_i;
	sc_out<bool> done_o;
	sc_out<sc_uint<LCM_WIDTH> > r_o;

	int gcd(int a, int b){
		for (;;){
			if (a == 0) return b;
			b %= a;
			if (b == 0) return a;
			a %= b;
		}
	}
	int compute_lcm(int a, int b){
		int temp = gcd(a, b);

		return temp ? (a / temp * b) : 0;
	}

	void p1() {
		if(!go_i.read()){
			done_o.write(false);
			return;
		}
		r_o.write(compute_lcm(x_i.read(), y_i.read()));
		done_o.write(true);
	}

	SC_CTOR(lcm) {
		SC_METHOD(p1);  
		sensitive << clk.pos() << x_i << y_i;
		reset_signal_is(reset, true);
	}
};
#endif

