-- Test bench to test FPGA implemented BEETNET transmitter
-- D. Beetner 3/03
--
-- Note: students must fill in constants given below

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;

entity trans_tb is end entity trans_tb;

architecture test of trans_tb is 
	-- constants that STUDENTS MUST FILL IN.
	-- (I have filled in some placeholder values)
	-- *****************************************
	constant clkper: time := 100 ns ;-- clock period
	constant clks_per_bit: integer:= 2; -- # of clocks for each bit transmitted
								-- (e.g. it takes 2 clocks to transmit 1 bit)
	-- *****************************************

	-- constants that I filled in.
	-- define resolution table for inverter
	TYPE stdlogic_1d_r IS ARRAY (std_logic) OF std_logic;
	CONSTANT inv_conv_vector: stdlogic_1d_r := 
		--      ---------------------------------------------
		--  in:    U    X    0    1    Z    W    L    H    - 
		--      ---------------------------------------------
				( 'U', 'X', 'H', '0', 'U', 'W', 'H', '0', '-'); -- out


	-- declare component under test (is matched automatically to
	-- entity of same name).
    component beetnet_trans is 
    	port(  
               data: in std_logic_vector(7 downto 0); -- data port
               WR,		-- write not 
			   CS,     		-- chip select
               CLK,     	-- clock input
               RESET: in std_logic; --active low write enable 
	           RDY: out std_logic;
               DSNS: in std_logic;
               DSND: out std_logic
             );
    end component;
   
    -- signals internal to testbench
    signal sig_data : std_logic_vector(7 downto 0);
    signal sig_WR, sig_CS, sig_RESET, sig_RDY : std_logic;
    signal clk : std_logic;
    signal sig_DSNS, sig_DSND : std_logic;

    signal dsnd_not : std_logic;
	signal sig_network: std_logic:='H';
    
    -- start achitecture definition
    begin
    
	-- instantiate the transmitter and hook up wires
    dut: beetnet_trans
    port map(	data => sig_data, WR => sig_WR, 
		CS => sig_CS, RESET => sig_RESET,  RDY => sig_RDY,
		clk => clk, DSNS => sig_DSNS, DSND => sig_DSND);
        
    -- generate clock
    clk_gen: process
    	begin
    		clk <= '1';
    		wait for clkper/2;
    		clk <= '0';
    		wait for clkper/2;
   	end process;

	-- create a virtual inverter that only weakly pulls the output high
	-- (see inv_conv_vector constant declaration for more info).
	dsnd_not <= inv_conv_vector(std_ulogic(sig_DSND));

	-- hook DSNS to output of inverter (which may also be driven by
	-- other external drivers/components)
	sig_DSNS <= dsnd_not;

	-- hook output of inverter to "rest of the network"
	dsnd_not <= sig_network;
        

	-- *********
	-- Define process which actually stimulates/tests transmitter
	-- *********

	stim_trans: process is

		-- define signals local to stim_trans
		variable val_sent: std_logic_vector (24 downto 0);

		-- define procedures local to stim_trans

		-- procedure to reset transmitter
		procedure reset_trans is
	    begin
		   sig_reset <= '1';
		   wait until clk'event and clk = '0';
		   wait until clk'event and clk = '0';
		   sig_reset <= '0';
		   wait until clk'event and clk = '0';
		end procedure reset_trans;

		-- procedure to load data into transmitter
		procedure load_data 
			(addr, dataH, dataL: in std_logic_vector (7 downto 0)) is
		begin

			-- load address
			sig_data <= addr;
			sig_CS <= '0';
			wait until clk'event and clk = '0';
			sig_WR <= '0';
			wait until clk'event and clk = '0';
			sig_CS <= '1';
			sig_WR <= '1';
			sig_data <= "ZZZZZZZZ";

			-- check that RDY is still low
			assert (sig_RDY = '0') 
				report "** sig_RDY going low too early!"
				severity error;

			-- load high byte of data
			sig_data <= dataH;
			sig_CS <= '0';
			wait until clk'event and clk = '0';
			sig_WR <= '0';
			wait until clk'event and clk = '0';
			sig_CS <= '1';
			sig_WR <= '1';
			sig_data <= "ZZZZZZZZ";

			-- check that RDY is still low
			assert (sig_RDY = '0') 
				report "** sig_RDY going low too early!"
				severity error;

			-- load low byte of data
			sig_data <= dataL;
			sig_CS <= '0';
			wait until clk'event and clk = '0';
			sig_WR <= '0';
			wait until clk'event and clk = '0';
			sig_CS <= '1';
			sig_WR <= '1';
			sig_data <= "ZZZZZZZZ";

		end procedure load_data;

		-- function to read value transmitted
		procedure received_data ( 
			temp: out std_logic_vector (24 downto 0)) is
		begin
			-- wait for start bit
			wait until sig_DSND'event and sig_DSND = '1';

			-- wait for 0.5 bit transmission periods before sampling 
			-- (sample in middle of bit)
			wait for clkper*clks_per_bit/2;

			for i in temp'range loop
				wait for clkper*clks_per_bit;
				temp(i) := sig_DSND;
			end loop;
		end procedure received_data;

	-- *********
	-- begin process stim_trans
	begin

	--- initialize value on pins
		report "initializing pins";
		sig_data <= "ZZZZZZZZ";
		sig_wr <= '1';
		sig_cs <= '1';
		sig_reset <= '0';

	--- reset state machine, variables, etc
		report "forcing reset";
		reset_trans;

	--- check initial states
	if (sig_RDY = '0') and (sig_DSND = '0') then
	     report "correct initial values";
	end if;
	assert (sig_RDY = '0') and (sig_DSND = '0')
		report "** Transmitter not producing appropriate values after reset!"
		severity error;
	
	-- ***
	report "check set 1";
	-- ***

	--- load transmitter with some data
	report "loading transmitter with data";
	load_data(x"42", x"14", x"A0");

	--- check value sent by transmitter
	report "Data loaded.  Checking value transmitted";
	received_data(val_sent);

	--- check value sent
	if ((val_sent(24 downto 17) = x"42") and
		(val_sent(16 downto 9) = x"14") and
		(val_sent(8 downto 1) = x"A0") and
		(val_sent(0) = '0')) then
	     	report "Correct values transmitted";
	end if;
	assert ((val_sent(24 downto 17) = x"42") and
		(val_sent(16 downto 9) = x"14") and
		(val_sent(8 downto 1) = x"A0") and
		(val_sent(0) = '0')) 
			report "Incorrect values transmitted!"
			severity error;
	
	-- check that stop bit is then sent
	wait for clkper*clks_per_bit;
	if (sig_DSND = '0') then
		report "stop bit sent correctly";
	end if;
	assert (sig_DSND = '0') 
		report "no stop bit!"
		severity error;
	wait for clkper*clks_per_bit/2;

	--- check that RDY goes low again after completing transmission
	wait until clk'event and clk = '0';
	if (sig_RDY = '0') then
	     report "Transmission completed successfully";
	end if;
	assert (sig_RDY = '0')
		report "RDY not reset to 0 after transmission!"
		severity error;
	
	-- ***
	report "check set 2";
	-- ***

	--- load transmitter with some data
	report "loading transmitter with data";
	load_data(x"2A", x"52", x"80");

	--- check that data not transmitted while network "busy"
	wait for 5*clkper*clks_per_bit;
	report "making network busy";
	sig_network <= '0';
	assert sig_DSND = '0'
		report "Transmitter is sending data while network is busy!"
		severity error;
	wait for 5*clkper*clks_per_bit;
	assert sig_DSND = '0'
		report "Transmitter is sending data while network is busy!"
		severity error;
	wait for 15*clkper*clks_per_bit;
	assert sig_DSND = '0'
		report "Transmitter is sending data while network is busy!"
		severity error;
	report "network is freeing up";
	sig_network <= 'H';

	--- check value sent by transmitter
	report "Checking value transmitted";
	received_data(val_sent);

	--- check value sent
	if ((val_sent(24 downto 17) = x"2A") and
		(val_sent(16 downto 9) = x"52") and
		(val_sent(8 downto 1) = x"80") and
		(val_sent(0) = '1')) then
	     	report "Correct values transmitted";
	end if;
	assert ((val_sent(24 downto 17) = x"2A") and
		(val_sent(16 downto 9) = x"52") and
		(val_sent(8 downto 1) = x"80") and
		(val_sent(0) = '1')) 
			report "Incorrect values transmitted!"
			severity error;
	
	-- check that stop bit is then sent
	wait until sig_DSND'event and sig_DSND = '0';

	-- ***
	-- anything else to check?
	report "If it were me, I'd probably check now to see what happens if line becomes busy AFTER transmission started.";
	report "Probably other things too";

	-- ***
	report "simulation complete!";
	wait;

    end process;

end architecture;



