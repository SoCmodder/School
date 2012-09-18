--------------------------------------------------------------------------
-- Package body for the Newton-Raphson method
-- by Joe Wingbermuehle 20020225
--------------------------------------------------------------------------

with Ada.Text_IO, Ada.Integer_Text_IO;

package body NewtonRaphson is

	------------------------------------------------------------------
	-- Evaluate an equation using the Newton-Raphson method
	------------------------------------------------------------------
	function Evaluate(eqn : Equation; derivative : Equation;
		guess : Real := 0.0; error : Real := 0.001)
		return Real is

		x	: Real;
		last	: Real;
		iter	: integer;

	begin

		Ada.Text_IO.Put("Newton-Raphson guess=");
		Real_IO.Put(guess);
		Ada.Text_IO.Put(", error=");
		Real_IO.Put(error);
		Ada.Text_IO.New_Line;

		Ada.Text_IO.Put("Iteration     Value         % Error");
		Ada.Text_IO.New_Line; 

		x := guess;
		iter := 0;
		last := 0.0;
		loop
			last := x;
			x := x - eqn(x) / derivative(x);
			iter := iter + 1;

			Ada.Integer_Text_IO.Put(iter);
			Ada.Text_IO.Put("  ");
			Real_IO.Put(x);
			Ada.Text_IO.Put("  ");
			Real_IO.Put((x - last) / x * 100.0);
			Ada.Text_IO.New_Line;

			exit when iter > 0
				and abs(x - last) / x <= error;

		end loop;

		return x;

	end Evaluate;

end NewtonRaphson;

