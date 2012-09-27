-- EXAMPLE
-- Creation of a resolved signal that determines
-- both a) the actual voltage at the input of
-- a logic gate, as determined by the number of
-- driving and driven gates, and b) the corresponding
-- logic level of that signal

entity top is
end entity top;

architecture a1 of top is
	constant R1:real:= 1000.0;
	constant R2:real:= 10000.0;
	constant Vcc:real:=5.0;
	constant Vih:real:=1.4;
	constant Vil:real:=1.0;
	type logic_val is (I, H, L, X); -- I indicates input.  X is unknown level
	type io_u is record
		lgc: logic_val;
		vlt: real;
	end record io_u;
	type io_u_array is array (natural range <>) of io_u;

	function io_resolved (values: in io_u_array) return io_u is
		variable x:io_u;
		variable m,n:real:=0.0;
		variable z:boolean:= false;
	begin
		-- If any outputs are low, then result is low
		for i in values'range loop
			if (values(i).lgc = L) then
				z := true;
			end if;
		end loop;

		if z then
			x.vlt :=0.0;
			x.lgc :=L;

			return x;
		else
			for i in values'range loop
				-- count the number of inputs and outputs
				if (values(i).lgc = a1.I) then  -- why a1.I?
					m := m+1.0;
				elsif (values(i).lgc = H) then
					n := n+1.0;
				end if;
			end loop;

			-- any outputs?
			if (n=0.0) then
				report "warning.  No outputs specified on I/O line";
				x.lgc := L;
				x.vlt := 0.0;
				return x;
			end if;	

			-- calculate voltage given number of inputs + outputs
			if (m>0.0) then
				x.vlt := Vcc*(R2/m)/(R1/n+R2/m);
			else
				x.vlt := Vcc;
			end if;

			-- determine corresponding logic level
			if (x.vlt >= Vih) then
				x.lgc := H;
			elsif (x.vlt <= Vil) then
				x.lgc := L;
			else
				x.lgc := a1.X; -- why a1.X?
			end if;

			return x;
		end if;
	end io_resolved;

	subtype io_r is io_resolved io_u;


	------------------------------------------
	-- OK, now let's perform a VERY quick test
	------------------------------------------
	signal s1:io_r;

begin
	p1: process is
	begin
		s1.lgc <= I; -- each process supplies a separate driver
		wait;
	end process;

	p2: process is
	begin
		s1.lgc <= H;
		wait for 1 ns;
		s1.lgc <= I; -- Inputs never change to outputs, but is just a test.
		wait for 1 ns;
		wait;
	end process;

	p3: process is
	begin
		s1.lgc <= H;
		wait;
	end process;
	
end architecture;

