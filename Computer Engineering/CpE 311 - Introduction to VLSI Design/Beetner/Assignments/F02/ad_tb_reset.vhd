-- Test bench to test FPGA implemented A/D converter
-- V. Shirgur and D. Beetner 11/02
--
-- Note: student must fill in constants given below
-- Feel free to change Vin from 1.0 volts to some other value.  
-- If it were me I'd test several.

library ieee;
use ieee.math_real.all; --For performing logarithmic calculations
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;

entity ad_tb is end entity ad_tb;

architecture test of ad_tb is 
	-- constants... STUDENTS MUST FILL IN.
	-- *****************************************
	constant clkper: time := 100 ns ;-- clock period
		-- maximum amount of time to wait until flagging an error
		-- (A/D not responding)
	constant maxdelay : time := 1000*clkper; 
	constant VOH: real := 42.0; -- V output high
	constant VOL: real := 42.0; -- V output low
	constant VIH: real := 42.0; -- V input high
	constant VIL: real := 42.0; -- V input low
	constant R: real := 42.0; -- value of external resistor
	constant C: real := 42.0; -- value of external capacitor
		-- expected value of high byte from A/D when vin = 1.0 volts
	constant data_high_vin1 : std_logic_vector(7 downto 0) := x"42"; 
		-- expected value of low byte from A/D when vin = 1.0 volts
	constant data_low_vin1 :  std_logic_vector(7 downto 0) := x"42"; 
	-- *****************************************

	-- other declarations within architecture 
    component adc is 
    	port(  clk,		--system clock
               RD,     		--active low read enable 
               ALE,     	--address latch enable 
               WR: in std_logic; --active low write enable 
               addr_data: inout std_logic_vector(7 downto 0); -- from/to port0 of 8051 
               CS0, CS1, CS2, CS3: in std_logic; -- from P2 of 8051 (for selecting ADC)
	         RDY: out std_logic;
               ain: inout std_logic;
		   reset: in std_logic
               );
    end component;
   
    -- signals internal to testbench
    signal sig_WR, sig_RD, sig_ALE : std_logic;
    signal sig_CS0, sig_CS1, sig_CS2, sig_CS3, sig_RDY, sig_reset : std_logic;
    signal sig_addr_data : std_logic_vector(7 downto 0);
    signal clk : std_logic;
    signal sig_ain: std_logic:='L';
    signal Vin:real:=0.0; --- input voltage

    type statetype is (s0, s1, s2); --defining the states
    signal currentstate: statetype:=s0;
    
    -- start achitecture definition
    begin
    
    dut: adc
    port map(	clk => clk, WR => sig_WR, RD => sig_RD, ALE => sig_ALE, 
    		addr_data => sig_addr_data, CS0 => sig_CS0, CS1 => sig_CS1, 
    		CS2 => sig_CS2, CS3 => sig_CS3, ain => sig_ain, RDY => sig_RDY, reset => sig_reset);
        
    -- generate clock
    clk_gen: process
    	begin
    		clk <= '1';
    		wait for clkper/2;
    		clk <= '0';
    		wait for clkper/2;
   	end process;
        
    -- determine when FPGA charging/discharging capacitance.  Set current state accordingly
    RC_state: process(sig_ain)
    	begin
   		 if (sig_ain = '0') then -- FPGA writes 0
   		    currentstate <= s0;
  		  elsif (sig_ain = '1') then -- FPGA writes 1
   		 	currentstate <= s1;
   		 elsif ((sig_ain = 'H') OR (sig_ain = 'L'))  then   --- FPGA writes 'Z'
   		 	currentstate <= s2;
   		 end if;
   	end process;
    
    -- determine when logic voltage input to Ain should change 
    -- signal level.  Signal change may be determined by time to charge/discharge
    -- capacitor.
    transitions: process (currentstate)
        variable timeH, timeL: time := 0 ns;
        variable integer_val_L, integer_val_H : integer := 0;
            
        begin
        case currentstate is
          when s0 =>
            sig_ain <= 'L';
          when s1 =>
            sig_ain <= 'H';
          when s2 =>
            if (sig_ain = 'L') then -- start charging
    	        if ((VOL < Vin) and (VIH < Vin)) then
    		    --Type Conversion.  Do calculation in nanoseconds
    		    timeL := (1 ns) * integer(1.0E9*R*C*log((VOL - Vin)/(VIH - Vin)));
    		    sig_ain <= 'H' after timeL; 
    	        end if;
    	      else 	-- start discharging
       	  if ((VOH > Vin) and (VIL > Vin)) then 
       		--Type Conversion
    	   	    timeH := (1 ns)*integer(1.0E9*R*C*log((VOH - Vin)/(VIL- Vin)));
    	   	    sig_ain <= 'L' after timeH; 
    	  	  end if;
    	      end if;  
        end case;
    end process;
    
    -- process to stimulate the AD converter (acts like the 8051)
    stim_ad: process
	
	  -- procedure to reset FPGA
	  procedure reset_ad is
	  begin
		sig_reset <= '0';
		wait until clk'event and clk = '0';
		wait until clk'event and clk = '0';
		sig_reset <= '1';
		wait until clk'event and clk = '0';
	  end procedure reset_ad;


	  -- procedure to start conversion
	  procedure start_cnv is
	  begin
	      sig_RD <= '1';
	      sig_WR <= '1';
	      sig_ALE <= '0';
	      sig_addr_data <= x"42"; -- check interface values given above
	      sig_CS0 <= '1';
	      sig_CS1 <= '1';
	      sig_CS2 <= '0';
	      sig_CS3 <= '0';
	
	      wait for 2*clkper;
	      wait until clk'event and clk = '0';
	      sig_ale <= '1';
	      wait until clk'event and clk = '0';
	      wait until clk'event and clk = '0';
	      sig_ale <= '0';
	      wait until clk'event and clk = '0';
	         --Set addr_data bus to Z so that values can be read from it
		sig_addr_data <= "ZZZZZZZZ"; 
		
	      wait until clk'event and clk = '0';
	      wait until clk'event and clk = '0';
	      sig_rd <= '0';
	      wait until clk'event and clk = '0';
	      wait until clk'event and clk = '0';
	      wait until clk'event and clk = '1';
	      sig_rd <= '1';
	  end procedure start_cnv;
	
	--This function is to convert a std_logic_vector to string for purposes of display only
	  function to_string(sv: Std_Logic_Vector) return string is
	  use Std.TextIO.all;
    	      variable bv: bit_vector(sv'range) := to_bitvector(sv);
    	      variable lp: line;
  	  begin
    	      write(lp, bv);
    	      return lp.all;
  	  end;	--end of function

	-- Begin stimulation process (stim_ad)
	begin 
	report "Checking that interface works correctly";

	-- setting Vin = 1.0 volts.  Students may wish to change.
	Vin <= 1.0;
	report "Vin is 1.0 Volts";

	--- reset state machine, variables, etc
	report "forcing reset";
	reset_ad;

	--- start conversion
	report "Start conversion";
	start_cnv;

	-- wait for RDY signal
	if (sig_RDY /= '0') then
	    wait until (sig_RDY = '0') for maxdelay;
	end if;

	-- report results to user
	if (sig_RDY = '0') then
	     report "conversion complete";
	end if;
	assert (sig_RDY = '0')
		report "A/D not responding! Ready still high after " & time'image(maxdelay)
		severity error;
	
	wait for 10*clkper;
	-- read converted value from A/D
	report "attempting to read low-byte of converted value from A/D";
	
	    sig_addr_data <= x"43";
	    wait for 2*clkper;
	
	    wait until clk'event and clk = '0';
	    sig_ale <= '1';
	    wait until clk'event and clk = '0';
	    wait until clk'event and clk = '0';
	    sig_ale <= '0';
	    wait until clk'event and clk = '0';
	    sig_addr_data <= "ZZZZZZZZ"; --Set the addr_data bus to Z so that values can be read from it

	    wait until clk'event and clk = '0';
	    assert (sig_addr_data = "ZZZZZZZZ")
	    report "FPGA writing to data lines when 8051 is not reading!"
	    severity error;
	
	    wait until clk'event and clk = '0';
	    sig_rd <= '0';
	    wait until clk'event and clk = '0';
	    wait until clk'event and clk = '0';
	    wait until clk'event and clk = '1';
	
	-- report results to user
	assert (sig_addr_data /= "ZZZZZZZZ")
		report "FPGA not writing to data lines when 8051 is reading low byte!"
		severity error;
	
	assert (sig_addr_data = data_low_vin1)
		report "incorrect value from A/D.  Expected " & to_string(data_low_vin1) & " got " & to_string(sig_addr_data)
		severity error;
	if (sig_addr_data = data_low_vin1) then
		report "low byte read successfully from A/D";
	end if;

	sig_rd <= '1';
	
	wait until clk'event and clk = '0';
	wait for 10*clkper;

	report "attempting to read high-byte of converted value from A/D WHILE CS0 = '0' ";
	sig_CS0 <= '0';
	sig_addr_data <= x"44";
	    wait for 2*clkper;
	
	    wait until clk'event and clk = '0';
	    sig_ale <= '1';
	    wait until clk'event and clk = '0';
	    wait until clk'event and clk = '0';
	    sig_ale <= '0';
	    wait until clk'event and clk = '0';
	    sig_addr_data <= "ZZZZZZZZ"; --Set the addr_data bus to Z so that values can be read from it

	    wait until clk'event and clk = '0';
	    assert (sig_addr_data = "ZZZZZZZZ")
		report "FPGA writing to data lines when 8051 is not reading!"
		severity error;
	
	    wait until clk'event and clk = '0';
	    sig_rd <= '0';
	    wait until clk'event and clk = '0';
	    wait until clk'event and clk = '0';
	    wait until clk'event and clk = '1';
	    
	    --result := sig_addr_data;	
	    sig_rd <= '1';
	    wait until clk'event and clk = '0';

	    -- report results to user
	    assert (sig_addr_data = "ZZZZZZZZ")
		report "FPGA writing to data lines when CS0 = '0'!"
		severity error;
		
	    if (sig_addr_data = "ZZZZZZZZ") then
		report "A/D did not respont when CS0 = 0 --- Good!";
	    end if;


	report "attempting to (correctly) read high-byte of converted value from A/D";
	    sig_CS0 <= '1';
	    sig_addr_data <= x"44";
	    wait for 2*clkper;
	
	    wait until clk'event and clk = '0';
	    sig_ale <= '1';
	    wait until clk'event and clk = '0';
	    wait until clk'event and clk = '0';
	    sig_ale <= '0';
	    wait until clk'event and clk = '0';
	    sig_addr_data <= "ZZZZZZZZ"; --Setting the addr_data bus to Z so that values can be read from it

	    wait until clk'event and clk = '0';
	    assert (sig_addr_data = "ZZZZZZZZ")
		report "FPGA writing to data lines when 8051 is not reading!"
		severity error;
	
	    wait until clk'event and clk = '0';
	    sig_rd <= '0';
	    wait until clk'event and clk = '0';
		wait until clk'event and clk = '0';
		wait until clk'event and clk = '1';

		assert (sig_addr_data = data_high_vin1)
			report "incorrect value from A/D.  Expected " & to_String(data_high_vin1) & " got " & to_String(sig_addr_data)
			severity error;	
		if (sig_addr_data = data_high_vin1) then
			report "high byte read successfully from A/D";
		end if;

		sig_rd <= '1';

		wait until clk'event and clk = '0';
		assert (sig_addr_data = "ZZZZZZZZ")
			report "FPGA not writing to data lines when 8051 is not reading!"
			severity error;

	wait for 10*clkper;

	--Testing with wrong address
	report "attempting to read 'bad address' from A/D";
		sig_addr_data <= x"00";
		wait for 2*clkper;
	
		wait until clk'event and clk = '0';
		sig_ale <= '1';
		wait until clk'event and clk = '0';
		wait until clk'event and clk = '0';
		sig_ale <= '0';
		wait until clk'event and clk = '0';
		sig_addr_data <= "ZZZZZZZZ"; 	--Setting the addr_data bus into Z so that values can be read from it

		wait until clk'event and clk = '0';
		assert (sig_addr_data = "ZZZZZZZZ")
			report "FPGA writing to data lines when 8051 is not reading!"
			severity error;
	
		wait until clk'event and clk = '0';
		sig_rd <= '0';
		wait until clk'event and clk = '0';
		wait until clk'event and clk = '0';
		wait until clk'event and clk = '1';
		-- report results to user
		assert (sig_addr_data = "ZZZZZZZZ")
			report "FPGA not writing to data lines when 8051 is reading high byte!"
			severity error;
		if (sig_addr_data = "ZZZZZZZZ") then
			report "A/D did not respond to bad address -- Good!";
		end if;

		-- reset read line
		sig_rd <= '1';
		wait until clk'event and clk = '1';
		wait for 10*clkper;

	report "simulation complete!";
	wait;

    end process;

end architecture;
