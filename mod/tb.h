#ifndef TB_H
#define TB_H

#include <systemc.h>
#include <mod.h>

SC_MODULE(tb_lcm) {
	sc_signal<sc_uint<MOD_WIDTH> > x_i, y_i, r_o;
	sc_clock clk;
	sc_signal<bool> reset, go_i, done_o;
	SC_CTOR(tb_lcm): clk("clk", 10, SC_NS, 0.5), mod1("mod") {
	   
		mod1.clk(clk);
		mod1.reset(reset);
		mod1.go_i(go_i);
		mod1.x_i(x_i);
		mod1.y_i(y_i);
		mod1.r_o(r_o);
		mod1.done_o(done_o);
		SC_THREAD(main);
		sensitive << done_o;
	}
	private:             
	  mod mod1; // x,y inputs to calculate, r is the value for checking.
	  void check(const sc_uint<MOD_WIDTH>& x, const sc_uint<MOD_WIDTH>& y, const sc_uint<MOD_WIDTH>& r) {
		sc_time start_time_stamp = sc_time_stamp();
		x_i.write(x);
		y_i.write(y);
		go_i.write(true);
		wait();
		auto end_time_stamp = sc_time_stamp();
		cout << "@: " << sc_time_stamp()
		<< ": " << x << "%" << y << " = " << r
		<< " duration: " << end_time_stamp - start_time_stamp << endl;
		assert(r_o.read() == r);
		go_i.write(false);
		wait();
	}
	void main() {
		check(0, 0, 0); // note 0 is not a valid input, please check this error
		check(5, 8, 5);
		check(15, 3, 0);
		check(30, 20, 10);
		x_i.write(0);
		y_i.write(0);
		sc_stop();
	}
};

#endif

