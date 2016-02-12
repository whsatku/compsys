#ifndef TB_H
#define TB_H

#include <systemc.h>
#include <lcm.h>

SC_MODULE(tb_lcm) {
	sc_signal<sc_uint<LCM_WIDTH> > x_i, y_i, r_o;
	sc_clock clk;
	sc_signal<bool> reset, go_i, done_o;
	SC_CTOR(tb_lcm): clk("clk", 10, SC_NS, 0.5), lcm1("lcm") {
	   
		lcm1.clk(clk);
		lcm1.reset(reset);
		lcm1.go_i(go_i);
		lcm1.x_i(x_i);
		lcm1.y_i(y_i);
		lcm1.r_o(r_o);
		lcm1.done_o(done_o);
		SC_THREAD(main);
		sensitive << done_o;
	}
	private:             
	  lcm lcm1; // x,y inputs to calculate, r is the value for checking.
	  void check(const sc_uint<LCM_WIDTH>& x, const sc_uint<LCM_WIDTH>& y, const sc_uint<LCM_WIDTH>& r) {
		sc_time start_time_stamp = sc_time_stamp();
		x_i.write(x);
		y_i.write(y);
		go_i.write(true);
		wait();
		assert(r_o.read() == r);
		auto end_time_stamp = sc_time_stamp();
		cout << "@: " << sc_time_stamp()
		<< ": lcm(" << x << "," << y << ") = " << r
		<< " duration: " << end_time_stamp - start_time_stamp << endl;
		go_i.write(false);
		wait();
	}
	void main() {
		check(0, 0, 0); // note 0 is not a valid input, please check this error
		check(5, 8, 40);
		check(15, 3, 15);
		check(30, 20, 60);
		x_i.write(0);
		y_i.write(0);
		sc_stop();
	}
};

#endif

