/************************************************
 *  File name  :  cppmatrix.h
 *  Function   :  Definition of the matrix class
 *  programmer :  Franck Xia, CS Department/UMR
 *  Creation   :  Jan. 26, 2002
 *  Update     :  Jan. 24, 2003
 ***********************************************/

 #include <iostream.h>

 class cppmatrix
 {
   private:
    int no_row;
    int no_col;
    int**  mat;                  // equivalent of mat[size1][size2]

   public:
    cppmatrix();
    cppmatrix( int row, int col );
    cppmatrix( const cppmatrix & c );    // copy constructor
    ~cppmatrix();

    int get_row() const;
    int get_column() const;

    cppmatrix operator+( const cppmatrix & a );
    cppmatrix operator-( const cppmatrix & a );
    cppmatrix operator*( const cppmatrix & a );

    friend ostream & operator<<( ostream & os, const cppmatrix & a );
    friend istream & operator>>( istream & is, cppmatrix & a );
 };
