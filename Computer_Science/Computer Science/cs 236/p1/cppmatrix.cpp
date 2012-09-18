#include "cppmatrix.h"

cppmatrix::cppmatrix()
{
   no_row = 0;
   no_col = 0;
   mat = NULL;
}

cppmatrix::cppmatrix(int row, int col)
{
   no_row = row;
   no_col = col;
   //Creates a new matrix
   mat = new int*[no_row+1];	
   for(int i = 1; i <= no_row; i++)
   {
      mat[i] = new int[no_col+1];
   }
}

cppmatrix::cppmatrix( const cppmatrix & c )
{
   no_row = c.no_row;
   no_col = c.no_col;
    
   //Creates a new matrix
   mat = new int*[no_row+1];	
   for(int i = 1; i <= no_row; i++)
   {
      mat[i] = new int[no_col+1];
   }
   //Copies one matrix to another
   for(int i = 1; i <= no_row; i++)
   {
      for(int j = 1; j <= no_col; j++)
      {
         mat[i][j] = c.mat[i][j];
      }
   }
}

int cppmatrix::get_row() const
{
   return(no_row);
}

int cppmatrix::get_column() const
{
   return(no_col);
}

istream & operator>>( istream & is, cppmatrix & a )
{
   for(int i=1; i <= a.no_row; i++)
   {
      for(int j=1; j <= a.no_col; j++)
      {
         is >> a.mat[i][j];
      }
   }
   return is;
}

ostream & operator<<( ostream & os, const cppmatrix & a )
{
   for(int i=1; i <= a.no_row; i++)
   {
      for(int j=1; j <= a.no_col; j++)
      {
         os << a.mat[i][j];
         os << " ";
         if(a.mat[i][j] < 10)
            os << " ";
      }
      os << endl;
   }
   return os;
}

cppmatrix cppmatrix::operator+( const cppmatrix & a )
{
   cppmatrix tmp(a);
   for(int i=1; i <= no_row; i++)
   {
      for( int j = 1; j <= no_col; j++)
      {
         tmp.mat[i][j] = mat[i][j] + a.mat[i][j];
      }
   }
   return tmp;
}

cppmatrix cppmatrix::operator-( const cppmatrix & a )
{
   cppmatrix tmp(a);
   for(int i=1; i <= no_row; i++)
   {
      for( int j = 1; j <= no_col; j++)
      {
         tmp.mat[i][j] = mat[i][j] - a.mat[i][j];
      }
   }
   return tmp;
}

cppmatrix cppmatrix::operator*( const cppmatrix & a )
{
   cppmatrix tmp(no_row, a.no_col); //Stores answer matrix 
   int iNum; //Temporarily stores answer values 
	
   //performs the matrix multiplication. i,j,k are all index values
   for (int i = 1; i <= no_row; i++)
   {
      for (int j = 1; j <= a.no_col; j++)
      {
         iNum = 0;
         for (int k = 1; k <= no_col; k++)
         {
            iNum += mat[i][k] * a.mat[k][j];
         }
         tmp.mat[i][j] = iNum;
      }
   }
   return tmp;
}

cppmatrix::~cppmatrix()
{
   //frees memory used by the matrix
   for (int c=1; c <= no_row; c++)
   {
      delete [] mat[c];
   }
   delete [] mat;
}



