--------------------------------------------------------------------------
-- Package specification for the integration functions
-- Joe Wingbermuehle 20020505
--------------------------------------------------------------------------

generic
package Integrate is

   subtype Value_Type is float;

   type Equation is access function(x : Value_Type) return Value_Type;

   function Trapezoidal(f : Equation; a, b : Value_Type;
      n : integer := 1) return Value_Type;

   function Simpsons(f : Equation; a, b : Value_Type;
      n : integer := 2) return Value_Type;

end Integrate;

