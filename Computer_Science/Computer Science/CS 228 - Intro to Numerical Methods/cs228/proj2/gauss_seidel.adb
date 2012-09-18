--------------------------------------------------------------------------
-- Implementation of the Gauss-Seidel method
-- Joe Wingbermuehle 20020403
--------------------------------------------------------------------------

with Ada.Text_IO; use Ada.Text_IO;

package body Gauss_Seidel is

   -----------------------------------------------------------------------
   -- Determine if there is a zero in the diagonal
   -----------------------------------------------------------------------
   function Is_Diagonal(matrix : Matrix_Type) return boolean is
   begin
      for x in matrix'range(1) loop
         if matrix(x, x) = Data_Type(0) then
            return false;
         end if;
      end loop;
      return true;
   end Is_Diagonal;

   -----------------------------------------------------------------------
   -- Swap rows in the matrix and result to eliminate zeros in the
   -- diagonal
   -----------------------------------------------------------------------
   procedure Align_Diagonals(matrix : in out Matrix_Type;
      result : in out Result_List; size : integer := 1) is

      temp         : Data_Type;

   begin
      if Is_Diagonal(matrix) then
         return;
      end if;
      for x in matrix'first(1) .. matrix'last(1) - size loop
         for y in matrix'range(2) loop
            temp := matrix(x, y);
            matrix(x, y) := matrix(x + size, y);
            matrix(x + size, y) := temp;
         end loop;
         temp := result(x);
         result(x) := result(x + size);
         result(x + size) := temp;
         if size < matrix'length(1) then
            Align_Diagonals(matrix, result, size + 1);
         end if;
         if Is_Diagonal(matrix) then
            return;
         end if;
         for y in matrix'range(2) loop
            temp := matrix(x, y);
            matrix(x, y) := matrix(x + size, y);
            matrix(x + size, y) := temp;
         end loop;
         temp := result(x);
         result(x) := result(x + size);
         result(x + size) := temp;
      end loop;
   end Align_Diagonals;

   -----------------------------------------------------------------------
   -- Solve the system of equations using the Guass-Seidel method
   -----------------------------------------------------------------------
   procedure Solve(result : out Result_List; matrix : in out Matrix_Type;
      max_error : float := 0.0) is
      total            : Data_Type;
      count            : integer;
      error, temp      : float;
   begin
      for x in result'range loop
         result(x) := 1.0;
      end loop;
      Align_Diagonals(matrix, result);
      if not Is_Diagonal(matrix) then
         raise Constraint_Error;
      end if;
      count := 0;
      loop
         count := count + 1;
         -- Loop through each equation
         error := 0.0;
         for x in matrix'range(1) loop
            total := matrix(x, matrix'last(2));
            -- Loop through each term
            for y in matrix'first(2) .. matrix'last(2) - 1 loop
               if y /= x then
                  total := total - result(y) * matrix(x, y);
               end if;
            end loop;
            total := total / matrix(x, x);
            temp := float((total - result(x)) / total);
            error := float'max(abs(temp), error);
            result(x) := total;
         end loop;
         exit when error <= max_error;
      end loop;
      Put_Line(count'img & " iteration(s)");
   end Solve;

   -----------------------------------------------------------------------
   -- Display the result
   -----------------------------------------------------------------------
   procedure Display(result : Result_List) is
   begin
      for x in result'range loop
         Put_Line("x(" & x'img & ") = "
            & result(x)'img);
      end loop;
   end Display;

   -----------------------------------------------------------------------
   -- Get a specific result
   -----------------------------------------------------------------------
   function Get_Result(result : Result_List; index : integer)
      return Data_Type is
   begin
      return result(index);
   end Get_Result;

end Gauss_Seidel;

