-- a quick LZ-encoder to test the testbench (kinda)

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;


entity LZ_encoder is
		port(
		  data: in std_logic_vector(7 downto 0); -- data port
		  WR,      -- write not
		  CS,          -- chip select not
		  CLK,         -- clock input
		  RESET: in std_logic; -- reset pin
		  RDY: out std_logic; -- RDY not -- back to microp
		  DOUT: out std_logic;
		  CLKOUT: out std_logic
		 );
end entity;

architecture test of LZ_encoder is

	TYPE outputrange is range 0 to 8*51-1;
	TYPE output_vec_type is ARRAY (outputrange) OF std_logic;
	CONSTANT expected_vec: output_vec_type :=
		X"000042_00002A_000052_000080_000012_000034_000056_000078_1C022A_1C0356_1C0542_0C0442_100342_1C0852_100142_010600_1F0200";

	begin

		write_data: process is
		begin
			-- wait for reset.. and a bit more
			CLKOUT <= '1';
			RDY <= '0';
			wait until RESET'event and RESET = '0';
			wait until clk'event and clk = '0';

			-- begin writing data out
			for i in outputrange loop
				CLKOUT <= '1';
				DOUT <= expected_vec(i);
				wait until clk'event and clk = '0';
				wait until clk'event and clk = '0';
				CLKOUT <= '0';
				wait until clk'event and clk = '0';
				wait until clk'event and clk = '0';
			end loop;

			report "Encoder finished sending output";

			wait;
		end process;
	end;


