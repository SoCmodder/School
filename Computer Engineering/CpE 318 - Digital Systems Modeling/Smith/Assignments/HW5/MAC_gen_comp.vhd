Library IEEE;
use IEEE.std_logic_1164.all;

entity DFF0 is
        port(clk, reset, D: in std_logic;
                 Q, nQ: out std_logic);
end;

architecture BEHAVIOR of DFF0 is
begin
	DFF: process
	begin
		wait until clk'event and clk = '1';
		if reset = '1' then
			Q <= '0';
			nQ <= '1';
		else
			Q <= D;
			nQ <= not D;
		end if;
	end process;
end BEHAVIOR;
Library IEEE;
use IEEE.std_logic_1164.all;

entity FA is
        port(x, y, c_in: in std_logic;
                s, c_out: out std_logic);
end;

architecture BEHAVIOR of FA is
begin
	s <= x xor y xor c_in;
	c_out <= (x and y) or (x and c_in) or (y and c_in);
end BEHAVIOR;
Library IEEE;
use IEEE.std_logic_1164.all;

entity HA is
        port(x, y: in std_logic;
                s, c_out: out std_logic);
end;

architecture BEHAVIOR of HA is
begin
	s <= x xor y;
	c_out <= x and y;
end BEHAVIOR;
Library IEEE;
use IEEE.std_logic_1164.all;

entity and2 is
	port(a, b: in STD_LOGIC;
		 z: out STD_LOGIC);
end;

architecture BEHAVIOR of and2 is
begin
	z <= a and b;
end BEHAVIOR;
-- generic 2s complement MAC X_len <= Y_len

Library IEEE;
use IEEE.std_logic_1164.all;

entity MAC is
	generic(X_len, Y_len: positive := 8;
		A_len: positive := 24);
	port(X: in std_logic_vector(X_len-1 downto 0);
		Y: in std_logic_vector(Y_len-1 downto 0);
		clk, reset: in std_logic;
		A: out std_logic_vector(A_len-1 downto 0);
		OV: out std_logic);
end;

architecture gen of MAC is
	type pp_type is array(X_len-1 downto 0, X_len+Y_len-2 downto 0) of std_logic;
	type struct is array(X_len+1 downto 2, X_len+Y_len-1 downto 1) of std_logic;
	signal pp: pp_type;
	signal c, s: struct;
	signal Ain, Aout, nAout: std_logic_vector(A_len-1 downto 0);
	signal rc: std_logic_vector(A_len downto X_len+1);
	signal OV_in, nOV: std_logic;

	component AND2
		port(a, b: in std_logic;
			z: out std_logic);
	end component;

	component DFF0
		port(clk, reset, D: in std_logic;
			Q, nQ: out std_logic);
	end component;

	component FA
		port(x, y, c_in: in std_logic;
			s, c_out: out std_logic);
	end component;

	component HA
		port(x, y: in std_logic;
			s, c_out: out std_logic);
	end component;
begin
	row: for i in 0 to X_len-1 generate
	begin
		column: for j in 0 to Y_len-1 generate
			AND_gate: AND2
				port map(X(i), Y(j), pp(i, i+j));
		end generate;
	end generate;

	HA00: HA
		port map(Aout(0), pp(0, 0), Ain(0), c(2, 1));

	first: for i in 1 to Y_len-1 generate
	begin
		half_add: HA
			port map(pp(0, i), pp(1, i), s(2, i), c(2, i+1));
	end generate;

        middle_r: for i in 2 to X_len-1 generate
		middle_c: for j in 0 to Y_len-3 generate
		begin
			LSA: if j = 0 generate
				full_add: FA
					port map(s(i, i+j-1), c(i, i+j-1), Aout(i+j-1), Ain(i+j-1), c(i+1, i+j));
			end generate;

                	full_add: FA
                        	port map(s(i, i+j), c(i, i+j), pp(i, i+j), s(i+1, i+j), c(i+1, i+j+1));

			MSA: if j = Y_len-3 generate
				full_add: FA
					port map(pp(i-1, i+j+1), c(i, i+j+1), pp(i, i+j+1), s(i+1, i+j+1), c(i+1, i+j+2));
			end generate;
		end generate;
        end generate;

	LSFA: FA
                port map(s(X_len, X_len-1), c(X_len, X_len-1), Aout(X_len-1), Ain(X_len-1), c(X_len+1, X_len));

	sec_last: for i in X_len to X_len+Y_len-3 generate
		full_add: FA
			port map(s(X_len, i), c(X_len, i), Aout(i), s(X_len+1, i), c(X_len+1, i+1));
	end generate;

	MSFA: FA
		port map(pp(X_len-1, X_len+Y_len-2), c(X_len, X_len+Y_len-2), Aout (X_len+Y_len-2), s(X_len+1, X_len+Y_len-2),
				c(X_len+1, X_len+Y_len-1));

                half_add: HA
                        port map(s(X_len+1, X_len), c(X_len+1, X_len), Ain(X_len), rc(X_len+1));

	LSRCA: for i in X_len+1 to X_len+Y_len-2 generate
		RCA: FA
			port map(s(X_len+1, i), c(X_len+1, i), rc(i), Ain(i), rc(i+1));
	end generate;

	MSLSRCA: FA
		port map(c(X_len+1, X_len+Y_len-1), rc(X_len+Y_len-1), Aout(X_len+Y_len-1), Ain(X_len+Y_len-1), rc(X_len+Y_len));

	MSRCA: for i in X_len+Y_len to A_len-1 generate
                RCA: HA
                        port map(Aout(i), rc(i), Ain(i), rc(i+1));
        end generate;

	OV_in <= rc(A_len);

	DFF: DFF0
		port map(clk, reset, OV_in, OV, nOV);

	reg: for i in 0 to A_len-1 generate
		DFF: DFF0
			port map(clk, reset, Ain(i), Aout(i), nAout(i));
	end generate;

	A <= Aout;
end gen;
