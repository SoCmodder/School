--------------------------------------------------------------------------
-- Implementation of Trapezoidal/Simpson integration functions
-- Joe Wingbermuehle 20020505
--------------------------------------------------------------------------

package body Integrate is

   -----------------------------------------------------------------------
   -- Perform integration using the Trapezoidal Rule
   -----------------------------------------------------------------------
   function Trapezoidal(f : Equation; a, b : Value_Type;
      n : integer := 1) return Value_Type is
      result      : Value_Type;
      h           : Value_Type := (b - a) / Value_Type(n);
   begin
      -- I ~= ((b - a) / 2n)(f(a) + 2f(a+h) + .. + f(b))
      result := f(a);
      for x in 2 .. n - 1 loop
         result := result + 2.0 * f(a + h * Value_Type(x - 1));
      end loop;
      result := result + f(b);
      result := (b - a) / (2.0 * Value_Type(n)) * result;
      return result;
   end Trapezoidal;

   -----------------------------------------------------------------------
   -- Perform integration using Simpson's 1/3 Rule
   -----------------------------------------------------------------------
   function Simpsons(f : Equation; a, b : Value_Type;
      n : integer := 2) return Value_Type is
      result      : Value_Type;
      h           : Value_Type := (b - a) / Value_Type(n);
      add         : Value_Type := 4.0;
   begin
      -- I ~= ((b - a) / 6)(f(a) + 4*f(a+h) + f(b))
      result := f(a);
      for x in 1 .. n - 1 loop
         result := result + add * f(a + h * Value_Type(x));
         if add = 4.0 then
            add := 3.0;
         else
            add := 4.0;
         end if;
      end loop;
      result := result + f(b);
      result := (b - a) / (3.0 * Value_Type(n)) * result;
      return result;
   end Simpsons;

end Integrate;

