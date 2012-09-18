--------------------------------------------------------------------------
-- Program to solve problem 8.20
-- by Joe Wingbermuehle 20020225
--------------------------------------------------------------------------

with Ada.Text_IO;
with Ada.Numerics.Generic_Elementary_Functions;

with NewtonRaphson, FalsePosition;

procedure P8_20 is

	type Real is new float;

	package FP is new Ada.Numerics.Generic_Elementary_Functions(Real);
	package OpenMethod is new NewtonRaphson(Real);
	package ClosedMethod is new FalsePosition(Real);
	package Real_IO is new Ada.Text_IO.Float_IO(Real);

	------------------------------------------------------------------
	-- Calculate the value of the function at a specific point
	------------------------------------------------------------------
	function Eqn(x : Real) return Real is
		result	: Real;
	begin
		result := 70.0 * FP.exp(-1.5 * x);
		result := result + 25.0 * FP.exp(-0.075 * x) - 9.0;
		return result;
	end Eqn;

	------------------------------------------------------------------
	-- Calculate the value of the derivative at a specific point
	------------------------------------------------------------------
	function Derivative(x : Real) return Real is
		result	: Real;
	begin
		result := -1.5 * 70.0 * FP.exp(-1.5 * x);
		result := result - 0.075 * 25.0 * FP.exp(-0.075 * x);
		return result;
	end Derivative;

	temp	: Real;
	error	: constant Real := 0.000001;

begin

	temp := OpenMethod.Evaluate(Eqn'access, Derivative'access,
		10.0, error);
	Ada.Text_IO.Put("Newton-Raphson solution: ");
	Real_IO.Put(temp);
	Ada.Text_IO.New_Line;
	Ada.Text_IO.New_Line;

	temp := ClosedMethod.Evaluate(Eqn'access, 5.0, 20.0, error);
	Ada.Text_IO.Put("False-Position solution: ");
	Real_IO.Put(temp);
	Ada.Text_IO.New_Line;

end P8_20;

