--------------------------------------------------------------------------
-- Package specification for the False-Position method
-- by Joe Wingbermuehle 20020225
--------------------------------------------------------------------------

with Ada.Text_IO;

generic
	type Real is digits <>;
package FalsePosition is

	type Equation is access function(x : Real) return Real;

	package Real_IO is new Ada.Text_IO.Float_IO(Real);

	function Evaluate(eqn : Equation;
		start : Real; stop : Real;
		error : Real := 0.001) return Real;


end FalsePosition;
