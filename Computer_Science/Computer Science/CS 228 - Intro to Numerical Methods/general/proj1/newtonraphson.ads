--------------------------------------------------------------------------
-- Package specification for the Newton-Raphson method
-- by Joe Wingbermuehle 20020225
--------------------------------------------------------------------------

with Ada.Text_IO;

generic
	type Real is digits <>;
package NewtonRaphson is

	package Real_IO is new Ada.Text_IO.Float_IO(Real);

	type Equation is access function(x : Real) return Real;

	function Evaluate(eqn : Equation; derivative : Equation;
		guess : Real := 0.0; error : Real := 0.001)
		return Real;

end NewtonRaphson;

