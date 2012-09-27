Library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_unsigned.all;

entity TB_MAC is
end;

architecture TESTBENCH of TB_MAC is
	signal clk, reset, OV: STD_LOGIC;
	signal X, Y: std_logic_vector(3 downto 0);
	signal A, temp: std_logic_vector(7 downto 0);
	signal temp_out: std_logic_vector(8 downto 0);
	signal incorrect_result, incorrect_OV: std_logic := '0';

	component MAC
            generic(X_len, Y_len: positive := 8;
                A_len: positive := 24);
            port(X: in std_logic_vector(X_len-1 downto 0);
                Y: in std_logic_vector(Y_len-1 downto 0);
                clk, reset: in std_logic;
                A: out std_logic_vector(A_len-1 downto 0);
                OV: out std_logic);
	end component;

begin
	UUT: MAC
		generic map(4, 4, 8)
		port map(X, Y, clk, reset, A, OV);

	X <= temp(7 downto 4);
	Y <= temp(3 downto 0);

	CLOCK: process
	begin
		clk <= '0';
		wait for 25 ns;
		clk <= '1';
		wait for 25 ns;
	end process;

	INC: process
	begin
		reset <= '1';
		wait for 50 ns;
		reset <= '0';
		temp <= "00000000";
		temp_out <= "000000000";
		loop
			wait until clk'event and clk = '1';
			temp_out <= temp_out + (X * Y);
			wait for 1 ns;
			if temp_out(7 downto 0) /= A then
				incorrect_result <= '1';
			end if;
			if temp_out(8) /= OV then
				incorrect_OV <= '1';
			end if;
			if temp_out(8) = '1' then
				temp_out(8) <= '0';
			end if;
                        wait until clk'event and clk = '0';
                        temp <= temp + '1';
		end loop;
	end process;

end TESTBENCH;

configuration CFG_TB_MAC of TB_MAC is
	for TESTBENCH
		for UUT: MAC
		end for;
	end for;
end;
