--------------------------------------------------------------------------
-- Program to solve problem 8.3
-- by Joe Wingbermuehle 20020225
--------------------------------------------------------------------------

with Ada.Text_IO;
with Ada.Numerics.Generic_Elementary_Functions;

with NewtonRaphson, FalsePosition;

procedure P8_3 is

	type Real is new float;

	package OpenMethod is new NewtonRaphson(Real);
	package ClosedMethod is new FalsePosition(Real);
	package FP is new Ada.Numerics.Generic_Elementary_Functions(Real);
	package Real_IO is new Ada.Text_IO.Float_IO(Real);

	------------------------------------------------------------------
	-- Calculate the value of the function at a specific point
	------------------------------------------------------------------
	function Eqn(x : Real) return Real is
		result	: Real;
	begin
		result := x / (1.0 - x);
		result := result * FP.sqrt(6.0 / (2.0 + x));
		result := result - 0.05;
		return result;
	end Eqn;

	------------------------------------------------------------------
	-- Calculate the value of the derivative at a specific point
	------------------------------------------------------------------
	function Derivative(x : Real) return Real is
		result	: Real;
	begin
		result := FP.sqrt(6.0) * (x ** 2 + x + 4.0);
		result := result * FP.sqrt(1.0 / (x + 2.0)) ** 3;
		result := result / (2.0 * (x - 1.0) ** 2);
		return result;
	end Derivative;

	temp	: Real;
	error	: constant Real := 0.000001;

begin

	temp := OpenMethod.Evaluate(Eqn'access, Derivative'access,
		0.25, error);
	Ada.Text_IO.Put("Newton-Raphson solution: ");
	Real_IO.Put(temp);
	Ada.Text_IO.New_Line;
	Ada.Text_IO.New_Line;

	temp := ClosedMethod.Evaluate(Eqn'access, 0.0, 0.5, error);
	Ada.Text_IO.Put("False-Position solution: ");
	Real_IO.Put(temp);
	Ada.Text_IO.New_Line;

end P8_3;

