-- A quick test bench to test the function of a simple LZ-encoder
-- D. Beetner 9/03
--
-- Note: students must fill in constants given below

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;

entity encoder_tb is end entity encoder_tb;

architecture test of encoder_tb is 
	-- constants that STUDENTS MUST FILL IN.
	-- (I have filled in some placeholder values)
	-- *****************************************
	constant clkper: time := 100 ns ;-- input clock period
	constant clkout_per_clk: integer:= 2; -- # of data output clock periods 
							--- for each input clock period
							-- (e.g. it takes 2 input clocks to transmit 1 bit)
	-- *****************************************

	-- constants that I filled in
	-- define inputs to encoder
	TYPE inputrange is range 0 to 50;
	TYPE outputrange is range 0 to 8*51-1;
	TYPE stdlogic_input IS ARRAY (inputrange) OF std_logic_vector(7 downto 0);
	CONSTANT input_vec: stdlogic_input :=
		( 0 => X"42", 1 => X"2A", 2 => X"52", 3 => X"80", 
		  4 => X"12", 5 => X"34", 6 => X"56", 7 => X"78", 
		  8 => X"12", 9 => X"34", 10 => X"2A", 11 => X"78", 
		  12 => X"12", 13 => X"34", 14 => X"56", 15 => X"78", 
		  16 => X"12", 17 => X"34", 18 => X"56", 19 => X"78", 
		  20 => X"42", 21 => X"2A", 22 => X"52", 23 => X"80", 
		  24 => X"12", 25 => X"42", 26 => X"2A", 27 => X"78", 
		  28 => X"12", 29 => X"42", 30 => X"2A", 31 => X"78", 
		  32 => X"12", 33 => X"42", 34 => X"2A", 35 => X"78", 
		  36 => X"12", 37 => X"42", 38 => X"52", 39 => X"80", 
		  40 => X"42", 41 => X"2A", 42 => X"78", 43 => X"12", 
		  44 => X"34", 45 => X"56", 46 => X"78",
		  others => X"00");

	TYPE output_vec_type is ARRAY (outputrange) OF std_logic;
	CONSTANT expected_vec: output_vec_type :=
		X"000042_00002A_000052_000080_000012_000034_000056_000078_1C022A_1C0356_1C0542_0C0442_100342_1C0852_100142_010600_1F0200";

	-- declare component under test (is matched automatically to
	-- entity of same name).
    component LZ_encoder is 
    	port(  
               data: in std_logic_vector(7 downto 0); -- data port
               WR,		-- write not 
			   CS,     		-- chip select not
               CLK,     	-- clock input
               RESET: in std_logic; -- reset pin
	           RDY: out std_logic; -- RDY not -- back to microp
               DOUT: out std_logic;
               CLKOUT: out std_logic
             );
    end component;
   
    -- signals internal to testbench
    signal sig_data : std_logic_vector(7 downto 0);
    signal sig_WR, sig_CS, sig_RESET, sig_RDY : std_logic;
    signal clk : std_logic;
    signal sig_CLKOUT, sig_DOUT : std_logic;

    -- start achitecture definition
    begin
    
	-- instantiate the transmitter and hook up wires
    dut: LZ_encoder
    port map(	data => sig_data, WR => sig_WR, 
		CS => sig_CS, RESET => sig_RESET,  RDY => sig_RDY,
		clk => clk, DOUT => sig_DOUT, CLKOUT => sig_CLKOUT);
        
    -- generate clock
    clk_gen: process
    	begin
    		clk <= '1';
    		wait for clkper/2;
    		clk <= '0';
    		wait for clkper/2;
   	end process;


	-- *********
	-- Define process to "receive" data.  
	-- *********
	receive: process is
		-- define signals local to receive
		variable received_vec: output_vec_type := (others => '0');
		variable i:outputrange:=0;
			

		begin 
			wait until sig_CLKOUT'event and sig_CLKOUT = '0' and sig_RESET = '0';
			received_vec(i) := sig_DOUT;
			assert (received_vec(0 to i) = expected_vec(0 to i))
				report "compressed result does not match expected result"
				severity error;
			assert (i<received_vec'right)
				report "Maximum received vector length reached. Simulation complete -- though you may want to test other things too!"
				severity failure;
			i := i + 1;
		end process;
	

	-- *********
	-- Define process to send data to LZ encoder
	-- *********

	write: process is

		-- define local variables

		-- procedure to reset transmitter
		procedure reset_trans is
	    begin
		   sig_reset <= '1';
		   wait until clk'event and clk = '0';
		   wait until clk'event and clk = '0';
		   sig_reset <= '0';
		   wait until clk'event and clk = '0';
		end procedure reset_trans;

		-- *** begin process ***
		begin

			-- set some initial values
			sig_wr <= '1';
			sig_cs <= '1';

			-- reset encoder
			reset_trans;

			for i in inputrange loop
				sig_data <= input_vec(i);
				sig_CS <= '0';
				wait until clk'event and clk = '0' and sig_RDY = '0';
				sig_WR <= '0';
				wait until clk'event and clk = '0';
				sig_CS <= '1';
				sig_WR <= '1';
				sig_data <= "ZZZZZZZZ";
				wait until clk'event and clk = '0';
			end loop;

			-- ***
			report "Finished loading data";
			wait;

		end process write;

end architecture;



