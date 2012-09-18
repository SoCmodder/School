--------------------------------------------------------------------------
-- Package specification for the Gauss-Seidel method
-- Joe Wingbermuehle 20020403
--------------------------------------------------------------------------

generic
   type Data_Type is digits <>;
package Gauss_Seidel is

   type Matrix_Type is array(positive range <>, positive range <>)
      of Data_Type;

   type Result_List is array(positive range <>) of Data_Type;

   procedure Solve(result : out Result_List; matrix : in out Matrix_Type;
      max_error : float := 0.0);

   procedure Display(result : Result_List);

   function Get_Result(result : Result_List; index : integer)
      return Data_Type;

end Gauss_Seidel;

