--------------------------------------------------------------------------
-- Package body for the False-Position method
-- by Joe Wingbermuehle 20020225
--------------------------------------------------------------------------

with Ada.Text_IO, Ada.Integer_Text_IO;

package body FalsePosition is

	------------------------------------------------------------------
	-- Evaluate an equation using the False-Position method
	------------------------------------------------------------------
	function Evaluate(eqn : Equation; start : Real;
		stop : Real; error : Real := 0.001) return Real is

		x, last		: Real;
		upper, lower	: Real;
		temp		: Real;
		iter		: integer;

	begin

		Ada.Text_IO.Put("False-Position start=");
		Real_IO.Put(start);
		Ada.Text_IO.Put(", stop=");
		Real_IO.Put(stop);
		Ada.Text_IO.Put(", error=");
		Real_IO.Put(error);
		Ada.Text_IO.New_Line;

		Ada.Text_IO.Put("Iteration     Value         % Error");
		Ada.Text_IO.New_Line; 

		lower := start;
		upper := stop;
		iter := 0;
		x := 0.0;
		loop

			last := x;
			x := eqn(upper) * (lower - upper);
			x := x / (eqn(lower) - eqn(upper));
			x := upper - x;

			temp := eqn(x);
			if temp < 0.0 then
				lower := x;
			else
				upper := x;
			end if;

			iter := iter + 1;

			Ada.Integer_Text_IO.Put(iter);
			Ada.Text_IO.Put("  ");
			Real_IO.Put(x);
			Ada.Text_IO.Put("  ");
			Real_IO.Put((x - last) / x * 100.0);
			Ada.Text_IO.New_Line;

			exit when iter > 1
				and abs(x - last) / x <= error;

		end loop;

		return x;
	end Evaluate;

end FalsePosition;

