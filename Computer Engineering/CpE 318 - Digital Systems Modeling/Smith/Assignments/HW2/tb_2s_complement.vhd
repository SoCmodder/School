Library IEEE;
use IEEE.std_logic_1164.all;
use work.twos_comp_arith.all;

entity tb_2s_complement is
end;

architecture testbench of tb_2s_complement is
signal a: twos_comp(7 downto 0) := "11001010"; -- 8, -54
signal b: twos_comp(12 downto 0) := "0100111110001"; -- 13, 2545
signal c: twos_comp(11 downto 0) := "100110101010"; -- 12, -1622
signal d: twos_comp(3 downto 0) := "0010"; -- 4, 2
signal e: twos_comp(6 downto 0) := "1110001"; -- 7, -15
signal f: twos_comp(15 downto 0) := "0001111110001010"; -- 16, 8074
signal g: twos_comp(8 downto 0) := "100000000"; -- 9, -256
signal h: twos_comp(11 downto 0) := "100000000000"; -- 12, -2048
signal test1, test5: twos_comp(13 downto 0);
signal test2, test6: twos_comp(12 downto 0);
signal test3, test7, test5a: twos_comp(12 downto 0);
signal test4, test8: twos_comp(16 downto 0);
signal test9, test13: twos_comp(20 downto 0);
signal test10: twos_comp(18 downto 0);
signal test11: twos_comp(15 downto 0);
signal test12: twos_comp(28 downto 0);
signal test2a: twos_comp(9 downto 0);
signal R1: twos_comp(7 downto 0);
signal Q1: twos_comp(12 downto 0);
signal R2: twos_comp(12 downto 0);
signal Q2: twos_comp(15 downto 0);
signal R3: twos_comp(8 downto 0);
signal Q3: twos_comp(11 downto 0);
signal R4: twos_comp(6 downto 0);
signal Q4: twos_comp(11 downto 0);
signal R5: twos_comp(12 downto 0);
signal Q5: twos_comp(7 downto 0);
signal i1, i2, i2a, i3, i4, i5a, i5, i6, i7, i8, i9, i10, i11, i12, i13, i14, i15, i16, i17, i18: std_logic := '0';
signal incorrect: std_logic;

begin

test1 <= a - b;
test2 <= c - e;
test2a <= e - g;
test3 <= d - c;
test4 <= b - f;

test5a <= h + h;
test5 <= a + b;
test6 <= c + e;
test7 <= d + c;
test8 <= b + f;

test9 <= a * b;
test10 <= c * e;
test11 <= d * c;
test12 <= b * f;
test13 <= g * h;

DIV: process(a)
	variable R1t: twos_comp(7 downto 0);
	variable Q1t: twos_comp(12 downto 0);
        variable R2t: twos_comp(12 downto 0);
        variable Q2t: twos_comp(15 downto 0);
        variable R3t: twos_comp(8 downto 0);
        variable Q3t: twos_comp(11 downto 0);
        variable R4t: twos_comp(6 downto 0);
        variable Q4t: twos_comp(11 downto 0);
        variable R5t: twos_comp(12 downto 0);
        variable Q5t: twos_comp(7 downto 0);
begin
	divide(b, a, Q1t, R1t);
	divide(f, b, Q2t, R2t);
	divide(h, g, Q3t, R3t);
        divide(c, e, Q4t, R4t);
        divide(a, b, Q5t, R5t);

	Q1 <= Q1t;
	R1 <= R1t;
        Q2 <= Q2t;
        R2 <= R2t;
        Q3 <= Q3t;
        R3 <= R3t;
        Q4 <= Q4t;
        R4 <= R4t;
        Q5 <= Q5t;
        R5 <= R5t;
end process;

P1: process
begin
	wait for 0 ns;
	if test1 /= "11010111011001" then -- -2599
		i1 <= '1';
	end if;
        if test2 /= "1100110111001" then -- -1607
                i2 <= '1';
        end if;
        if test2a /= "0011110001" then -- 241
                i2a <= '1';
        end if;
        if test3 /= "0011001011000" then -- 1624
                i3 <= '1';
        end if;
        if test4 /= "11110101001100111" then -- -5529
                i4 <= '1';
        end if;
        if test5a /= "1000000000000" then -- -4096
                i5a <= '1';
        end if;
        if test5 /= "00100110111011" then -- 2491
                i5 <= '1';
        end if;
        if test6 /= "1100110011011" then -- -1637
                i6 <= '1';
        end if;
        if test7 /= "1100110101100" then -- -1620
                i7 <= '1';
        end if;
        if test8 /= "00010100101111011" then -- 10619
                i8 <= '1';
        end if;
        if test9 /= "111011110011100101010" then -- -137430
                i9 <= '1';
        end if;
        if test10 /= "0000101111100001010" then -- 24330
                i10 <= '1';
        end if;
        if test11 /= "1111001101010100" then -- -3244
                i11 <= '1';
        end if;
        if test12 /= "00001001110011000101011101010" then -- 20548330
                i12 <= '1';
        end if;
	if test13 /= "010000000000000000000" then -- 524288
		i13 <= '1';
	end if;
        if Q1 /= "1111111010001" or R1 /= "00000111" then -- -47 R 7 
                i14 <= '1';
        end if;
        if Q2 /= "0000000000000011" or R2 /= "0000110110111" then -- 3 R 439
                i15 <= '1';
        end if;
        if Q3 /= "000000001000" or R3 /= "000000000" then -- 8 R 0
                i16 <= '1';
        end if;
        if Q4 /= "000001101100" or R4 /= "1111110" then -- 108 R -2 
                i17 <= '1';
        end if;
        if Q5 /= "00000000" or R5 /= "1111111001010" then -- 0 R -54
                i18 <= '1';
        end if;
	wait for 10 ns;
	wait;
end process;

incorrect <= i1 or i2 or i2a or i3 or i4 or i5a or i5 or i6 or i7 or i8 or i9 or i10 or i11 or i12 or i13 or i14 or i15 or i16 or i17 or i18;

end testbench;

configuration CFG_TB_2s_complement of TB_2s_complement is
        for TESTBENCH
        end for;
end;
