--------------------------------------------------------------------------
-- Program to solve problem 12.8
-- Joe Wingbermuehle 20020403
--------------------------------------------------------------------------

with Ada.Text_IO; use Ada.Text_IO;
with Gauss_Seidel;

procedure P12_8 is

   subtype Data_Type is float;
   package Solver is new Gauss_Seidel(Data_Type);

   matrix1   : Solver.Matrix_Type(1 .. 5, 1 .. 6) := (
         (-11.0,  10.0,   0.0,   0.0,   0.0, -0.1),
         (  1.0, -11.0,  10.0,   0.0,   0.0,  0.0),
         (  0.0,   1.0, -11.0,  10.0,   0.0,  0.0),
         (  0.0,   0.0,   1.0, -11.0,  10.0,  0.0),
         (  0.0,   0.0,   0.0,   1.0, -11.0,  0.0)
      );

   result   : Solver.Result_List(1 .. 5);

   temp      : Data_Type;

begin

   Put_Line("y values:");
   Solver.Solve(result, matrix1);
   Solver.Display(result);

   New_Line;
   Put_Line("x values:");
   -- K = x(i) / y(i) -> x(i) = 5 * y(i)
   for x in result'range loop
      temp := Solver.Get_Result(result, x) * 5.0;
      Put_Line("x(" & x'img & ") = " & temp'img);
   end loop;

end P12_8;

