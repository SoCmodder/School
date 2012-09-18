--------------------------------------------------------------------------
-- CS 228 Problem 21.25
-- Joe Wingbermuehle 200200505
--------------------------------------------------------------------------

with Ada.Text_IO; use Ada.Text_IO;
with Integrate;

procedure P21_25 is

   package Int is new Integrate;
   use Int;

   function V(x : Value_Type) return Value_Type is
   begin
      return 4.0 + 0.15 * x ** 2;
   end V;

   t, s      : Value_Type;

begin

   t := Trapezoidal(V'access, 0.0, 11.0, 183);
   s := Simpsons(V'access, 0.0, 11.0);

   Put_Line("Trapezoidal: " & t'img);
   Put_Line("Simpson's: " & s'img);

end P21_25;

