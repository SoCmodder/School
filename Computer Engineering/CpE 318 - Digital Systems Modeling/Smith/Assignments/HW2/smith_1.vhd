Library IEEE;
use IEEE.std_logic_1164.all;

package twos_comp_arith is

	type  twos_comp is array (natural range <>) of std_logic;

	function "+"(L: twos_comp; R: twos_comp) return twos_comp;
        function "-"(L: twos_comp; R: twos_comp) return twos_comp;
        function "*"(L: twos_comp; R: twos_comp) return twos_comp;
	procedure divide(dividend, divisor: in twos_comp; quotient, remainder: out twos_comp);

end twos_comp_arith;

package body twos_comp_arith is

        function "+"(L: twos_comp; R: twos_comp) return twos_comp is
	variable Rt: twos_comp(R'length-1 downto 0);
	variable Lt: twos_comp(L'length-1 downto 0);
	variable result_L, signx_LL, signx_LR: twos_comp(L'length downto 0); -- L longer
	variable result_R, signx_RL, signx_RR: twos_comp(R'length downto 0); -- R longer
	variable carry: std_logic := '0';
	begin
		Rt := R;
		Lt := L;
		if L'length > R'length then
			signx_LL(L'length) := Lt(L'length-1);
			signx_LL(L'length-1 downto 0) := Lt;
			for k in L'length downto R'length loop
				signx_LR(k) := Rt(R'length-1);
			end loop;
			signx_LR(R'length-1 downto 0) := Rt;
			for i in 0 to L'length loop
				result_L(i) := signx_LL(i) xor signx_LR(i) xor carry;
				carry := (signx_LL(i) and signx_LR(i)) or (signx_LL(i) and carry) or (signx_LR(i) and carry);
			end loop;
			return result_L;
		else 
                        signx_RR(R'length) := Rt(R'length-1);
                        signx_RR(R'length-1 downto 0) := Rt;
                        for j in R'length downto L'length loop
                                signx_RL(j) := Lt(L'length-1);
                        end loop;
                        signx_RL(L'length-1 downto 0) := Lt;
			for y in 0 to R'length loop
                                result_R(y) := signx_RL(y) xor signx_RR(y) xor carry;
                                carry := (signx_RL(y) and signx_RR(y)) or (signx_RL(y) and carry) or (signx_RR(y) and carry);
                        end loop;
                        return result_R;
		end if;
	end;

        function "-"(L: twos_comp; R: twos_comp) return twos_comp is
	variable Rt: twos_comp(R'length-1 downto 0);
        variable Lt: twos_comp(L'length-1 downto 0);
        variable signx_LL, result_L, signx_LR: twos_comp(L'length downto 0); -- L longer
        variable signx_RL, result_R, signx_RR: twos_comp(R'length downto 0); -- R longer
	variable carry: std_logic := '1';
        begin
		Rt := R;
                Lt := L;
                if L'length > R'length then
                        signx_LL(L'length) := Lt(L'length-1);
                        signx_LL(L'length-1 downto 0) := Lt;
                        for x in L'length downto R'length loop
                                signx_LR(x) := not(Rt(R'length-1));
                        end loop;
			for k in R'length-1 downto 0 loop
				signx_LR(k) := not(Rt(k));
			end loop;
			for i in 0 to L'length loop
                                result_L(i) := signx_LL(i) xor signx_LR(i) xor carry;
                                carry := (signx_LL(i) and signx_LR(i)) or (signx_LL(i) and carry) or (signx_LR(i) and carry);
                        end loop;
                        return result_L;
                else 
                        signx_RR(R'length) := not(Rt(R'length-1));
			for j in R'length-1 downto 0 loop
                                signx_RR(j) := not(Rt(j));
                        end loop;
                        for z in R'length downto L'length loop
                                signx_RL(z) := Lt(L'length-1);
                        end loop;
                        signx_RL(L'length-1 downto 0) := Lt;
			for y in 0 to R'length loop
                                result_R(y) := signx_RL(y) xor signx_RR(y) xor carry;
                                carry := (signx_RL(y) and signx_RR(y)) or (signx_RL(y) and carry) or (signx_RR(y) and carry);
                        end loop;
                        return result_R;
                end if;
        end;

        function "*"(L: twos_comp; R: twos_comp) return twos_comp is
	variable Rt: twos_comp(R'length-1 downto 0);
        variable Lt: twos_comp(L'length-1 downto 0);
	variable result, pp: twos_comp(L'length+R'length-1 downto 0);
	variable temp_result: twos_comp(L'length+R'length downto 0);
	variable L_us: twos_comp(L'length-1 downto 0);
        variable R_us: twos_comp(R'length-1 downto 0);
	variable comp_result, carry: std_logic;
        begin
		Rt := R;
                Lt := L;
		comp_result := Lt(L'length-1) xor Rt(R'length-1);
		if Lt(L'length-1) = '1' then
			carry := '1';
			for i in 0 to L'length-1 loop
                                L_us(i) := not(Lt(i)) xor carry;
                                carry := not(Lt(i)) and carry;
                        end loop;
		else
			L_us := Lt;
		end if;
                if Rt(R'length-1) = '1' then
			carry := '1';
                        for j in 0 to R'length-1 loop
                                R_us(j) := not(Rt(j)) xor carry;
                                carry := not(Rt(j)) and carry;
                        end loop;
                else
                        R_us := Rt;
                end if;
		for k in temp_result'length-1 downto 0 loop
			temp_result(k) := '0';
		end loop;
		for x in 0 to R'length-1 loop
			for y in 0 to pp'length-1 loop
				if (R_us(x)) = '0' then
					pp(y) := '0';
				elsif y < x then
					pp(y) := '0';
				elsif y-x > l'length-1 then
					pp(y) := '0';
				else
					pp(y) := l_us(y-x);
				end if;
			end loop;
			temp_result := temp_result(result'range) + pp;
		end loop;
		if comp_result = '1' then
			carry := '1';
			for z in 0 to result'length-1 loop
				result(z) := not(temp_result(z)) xor carry;
                                carry := not(temp_result(z)) and carry;
			end loop;
		else
			result := temp_result(result'range);
		end if;
		return result;
	end;

        procedure divide(dividend, divisor: in twos_comp; quotient, remainder: out twos_comp) is
        variable Q, divd: twos_comp(dividend'length-1 downto 0);
        variable R, D, divr: twos_comp(divisor'length-1 downto 0);
        variable Z: twos_comp(dividend'length+divisor'length-1 downto 0);
	variable sub: twos_comp(divisor'length+1 downto 0);
	variable carry, cR, cQ: std_logic;
	variable vec: std_logic_vector(1 downto 0);
        begin
		divd := dividend;
		divr := divisor;
		if divr(D'length-1) = '1' then
                        carry := '1';
                        for i in 0 to D'length-1 loop
                                D(i) := not(divr(i)) xor carry;
                                carry := not(divr(i)) and carry;
                        end loop;
                else
                        D := divr;
                end if;
		for j in Z'length-1 downto Q'length loop
                        Z(j) := '0';
                end loop;
                if dividend(Q'length-1) = '1' then
                        carry :='1';
                        for k in 0 to Q'length-1 loop
                                Z(k) := not(divd(k)) xor carry;
                                carry := not(divd(k)) and carry;
                        end loop;
                else
                        Z(Q'range) := divd;
                end if;
                for x in Q'length-1 downto 0 loop
			sub := Z(x+D'length downto x) - twos_comp('0' & D);
                        if sub(D'length+1) = '0' then
                                Z(x+D'length downto x) := sub(D'length downto 0);
                                Q(x) := '1';
                        else
                                Q(x) := '0';
                        end if;
                end loop;
                R := Z(R'length-1 downto 0);
		vec := divd(Q'length-1) & divr(D'length-1);
		case vec is
			when "00" =>
				cR := '0';
				cQ := '0';
			when "01" =>
				cR := '0';
				cQ := '1';
			when "10" =>
				cR := '1';
				cQ := '1';
			when others =>
				cR := '1';
				cQ := '0';
		end case;
		if cQ = '1' then
 			carry := '1';
                        for y in 0 to Q'length-1 loop
                                quotient(y) := not(Q(y)) xor carry;
                                carry := not(Q(y)) and carry;
                        end loop;
		else
			quotient := Q;
		end if;
                if cR = '1' then
                        carry := '1';
                        for s in 0 to R'length-1 loop
                                remainder(s) := not(R(s)) xor carry;
                                carry := not(R(s)) and carry;
                        end loop;
                else
                        remainder := R;
                end if;
        end divide;

end twos_comp_arith;
