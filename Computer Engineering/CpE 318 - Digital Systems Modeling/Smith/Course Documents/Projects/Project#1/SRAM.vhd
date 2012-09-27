Library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_unsigned.all;

entity SRAM is
	generic(A_len, D_len: positive);
	port(address: in std_logic_vector(A_len-1 downto 0);
		RW, E: in std_logic;
		data: inout std_logic_vector(D_len-1 downto 0));
end;

architecture behavior of SRAM is
	type memory is array (2**A_len-1 downto 0) of std_logic_vector(D_len-1 downto 0);
	signal mem: memory;
	signal Ed, RWd, VW: std_logic;
	signal Ad: std_logic_vector(A_len-1 downto 0);
	signal Dd: std_logic_vector(D_len-1 downto 0);
begin
	Ed <= E after 2 ns;
	RWd <= RW after 2 ns;
	Dd <= data after 1 ns;
	Ad <= address after 1 ns;

	P1: process(address, RW, E, data, Ed, RWd, Ad, Dd)
	begin
		if E = '1' and RW = '0' and E = Ed and RW = RWd then
			mem(conv_integer(Ad)) <= Dd;
			data <= (others => 'Z');
		elsif E = '1' and RW = '1' then
			data <= mem(conv_integer(address));
		else
			data <= (others => 'Z');
		end if;
	end process;
end behavior;
