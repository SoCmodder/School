--------------------------------------------------------------------------
-- Program to solve problem 12.13
-- Joe Wingbermuehle 20020403
--------------------------------------------------------------------------

with Ada.Text_IO; use Ada.Text_IO;
with Ada.Numerics.Elementary_Functions;
use Ada.Numerics.Elementary_Functions;

with Gauss_Seidel;

procedure P12_13 is

   subtype Data_Type is float;
   package Solver is new Gauss_Seidel(Data_Type);

   cos30          : constant Data_Type := Sqrt(3.0) / 2.0;
   cos45, sin45   : constant Data_Type := Sqrt(2.0) / 2.0;

   matrix      : Solver.Matrix_Type(1 .. 8, 1 .. 10) := (
      (-cos30, -cos45, 0.0, 0.0, -cos45, 0.0, 0.0, 0.0, 0.0, -1200.0),  -- Ax
      (-0.5, -sin45, 0.0, 0.0, -sin45, 0.0, 0.0, 0.0, 0.0, -600.0),     -- Ay
      (cos30, 0.0, 0.0, -1.0, 0.0, -1.0, 0.0, 0.0, 0.0, 0.0),           -- Bx
      (0.5, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 0.0, 0.0),              -- By
      (0.0, 0.0, -1.0, 1.0, cos45, 0.0, 0.0, 0.0, 0.0, 0.0),            -- Cx
      (0.0, 0.0, 0.0, 0.0, sin45, 0.0, 0.0, 0.0, 0.0, 0.0),             -- Cy
      (0.0, cos45, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0),            -- Dx
      (0.0, sin45, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 0.0)             -- Dy
   );

   result      : Solver.Result_List(1 .. 9);

begin

   Solver.Solve(result, matrix);
   Solver.Display(result);

end P12_13;
