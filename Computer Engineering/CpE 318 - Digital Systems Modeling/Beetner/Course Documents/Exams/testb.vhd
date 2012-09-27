
-- Testbench for takehome exam, CpE318, 4/2001.
-- 
-- Created by Shivappa Manjunath and Vivik Kushoo
-- 4/2001.
--
-- Note: overflow is checked manually, as are results
-- for the real-bit_vector conversion.
-- 

use work.all;
entity polytest is
end;

architecture behavior of polytest is
	constant Tpw : time := 50 ns;
	constant cycl : integer := 20;
	signal load,clk: bit;
	signal data,result: real:= 0.0;
	signal ovf: bit;
	
begin
	-- Instantiate test model.  
	-- You may have to change architecture name
	to_cal : entity work.poly_calc_test(calc_test) 
		 port map(load => load, data => data, clk => clk, result => result, ovf => ovf);
	
	clk_gen : process is
		begin
			clk <= '1' after Tpw, '0' after 2*Tpw;
			wait for 2*Tpw;
		end process clk_gen;
	
	cal_pro : process is
		variable x, res, d1,d2,fx : real := 0.0;
		
		begin
			
		------------------------------------------------------
		-- Pass 1: test the poly e^-x = 1-x+.5*x**2
		------------------------------------------------------
		
		-- load values
		wait until clk = '0';
		load <= '1';
		data <= 1.0; wait until clk = '0';
		data <= -0.095; wait until clk = '0';
		data <= 0.01; wait until clk = '0';
		load <= '0';
		
		-- check results for pass 1 
		-- should not overflow for this test
		x := 0.0;
		for i in 1 to cycl loop
			x := x + 0.1;
			res := 1.0 - x + 0.5*x**2;
			wait until clk = '0';
			assert abs(res - result) < 0.005
				report "deviation out of range, pass1 failed" 
				severity warning;
		end loop;	  	
		
			
		------------------------------------------------------
		-- Pass 2: check the poly f(x) = 4x**2 + 2*x - 3
		-- _could_ cause an overflow in the positive direction
		------------------------------------------------------
		
		-- load coefficient
		wait until clk = '0';
		load <= '1';
		data <= -1.0; wait until clk = '0';
		data <= -0.56; wait until clk = '0';
		data <= 0.08; wait until clk = '0';
		load <= '0';
		
		-- check results for pass 2
		
		x := -1.0;
		for i in 1 to 2*cycl loop
			x := x + 0.1;
			res := 4.0*x**2 + 2.0*x - 3.0;
			wait until clk = '0';
			assert abs(res - result) < 0.05
				report "deviation out of range, pass2 failed"
				severity warning;
		end loop;
	
		
		------------------------------------------------------
		-- Pass 5: check that running load for less than
		-- 3 clock cycles will at least disrupt results.
		-- Best case: model produces a warning report.
		-- results checked visually.
		------------------------------------------------------
		
		-- go through a load sequence
		wait until clk = '0';
		load <= '1';
		data <= -7.0; wait until clk = '0';
		load <= '0';
		wait until clk = '0'; -- should see an "odd result" or
		wait until clk = '0'; -- report in through here. (check visually)
		load <= '1';
		data <= -7.0; wait until clk = '0';
		data <= 0.58; wait until clk = '0';
		data <= -0.04; wait until clk = '0';
		load <= '0';
		
		-- check results for pass 5.  Results should be OK now.
		x := -1.0;
		for i in 1 to cycl loop
			x := x + 0.1;
			res := -2.0*x**2 + 2.0*x - 3.0;
			wait until clk = '0';
			assert abs(res - result) < 0.05
				report "deviation out of range, pass5 failed"
				severity warning;
		end loop;
			
		------------------------------------------------------
		-- Pass 4.  Load the polynomial with coefficients, etc,
		-- which cannot be represented directly by the bit vector
		-- input/outputs.  Test results for accuracy.
		------------------------------------------------------

		-- Loading the poly f(x) = 0.33333x**2 + 3.1415*x + 1
		wait until clk = '0';
		load <= '1';
		data <= 4.4748; 
		fx := 4.4748;
		wait until clk = '0';
		data <= 0.3842; 
		d1 := 0.3842;
		wait until clk = '0';
		data <= 0.0667; 
		d2 := 0.0667;
		wait until clk = '0';
		load <= '0';
		
		-- check results for pass 4.
		for i in 1 to cycl loop 
			res := fx + d1;
			fx := res;
			d1 := d1 + d2;
			d2 := d2;
			wait until clk = '0';
			assert  abs(res - result) > 0.05
				report "deviation out of range, pass4 failed"
				severity warning;
		end loop;
				
		------------------------------------------------------
		-- Pass 3: check the poly f(x) = -2x**2 + 2*x - 3
		-- Should produce an overflow in the negative direction.
		------------------------------------------------------

		-- load coefficients
		wait until clk = '0';
		load <= '1';
		data <= -7.0; wait until clk = '0';
		data <= 0.58; wait until clk = '0';
		data <= -0.04; wait until clk = '0';
		load <= '0';
		
		-- check results for pass 3
		x := -1.0;
		for i in 1 to 70*cycl loop
			x := x + 0.1;
			res := -2.0*x**2 + 2.0*x - 3.0;
			wait until clk = '0';
			assert abs(res - result) < 0.05
				report "deviation out of range, pass3 failed"
				severity warning;
		end loop;
		
	wait;
	end process cal_pro;
end architecture behavior;
		
