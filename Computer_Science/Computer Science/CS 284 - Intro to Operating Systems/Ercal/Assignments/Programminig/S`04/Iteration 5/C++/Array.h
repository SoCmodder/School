#ifndef Array_h
#define Array_h

// Author: Matt Johnson
// FileName: Array.h
// Course: CS 328 - Object Oriented Numerical Modeling I
// Instructor: Clayton Price 
// 
// This class defines a container which provides an array style interface.
// 
// Current Version is 1.0.
// 
// Revision History
// ----------------
// February 25, 2004
// Version 1.0:
// - Created Class.

#include <iostream>
#include <fstream>

using std::istream;
using std::ostream;

template<typename NumTmpl>
class Array
{
   // PreConditions:  The ostream must be open and poised to write. 
   // PostConditions: Contents of the array will be written to the ofile. 
   friend ostream& operator<< <>(ostream& ofile, 
                                 const Array<NumTmpl>& arr);

   // PreConditions:  The istream must be open and poised to read an 
   //                 Array. Specifically, the length of the array must be 
   //                 set to the number of elements in the istream. 
   //                 (use the SetLength member function)
   // PostConditions: The array has been defined from the istream.
   friend istream& operator>> <>(istream& ifile, Array<NumTmpl>& arr);

   public:
      // Constructor
      // PreConditions:  If desired, the length of the array may be 
      //                 specified.
      // PostConditions: Object has been created.
      Array(const unsigned int length = 10);

      // Copy Constructor
      // PreConditions:  None.
      // PostConditions: A new object has been created in the image of the
      //                 object passed in to the constructor.
      Array(const Array & original);

      // Destructor
      // PreConditions:  None.
      // PostConditions: Exogenous data has been released to the operating 
      //                 system.
      virtual ~Array();

      // PreConditions:  None.
      // PostConditions: Calling object is identical to the object passed 
      //                 into the assignment operator
      const Array& operator=(const Array & original);

      // PreConditions:  The index must be valid.
      // PostConditions: The data stored at the specified index is 
      //                 returned. 
      NumTmpl& operator[](const unsigned int &index) const;

      // PreConditions:  None.
      // PostConditions: Array is completely empty.
      bool Clear();

      // PreConditions:  None.
      // PostConditions: The length of the array is returned.
      unsigned int GetLength();

      // PreConditions:  The new length must be a positive integer and 
      //                 the system must be able to allocate that amount
      //                 of memory.
      // PostConditions: The length of the array is the specified length.
      //                 If that length is shorter than the original, the
      //                 array has been truncated.
      void SetLength(const unsigned int newLength);

      // PreConditions:  The array index must be valid, and the value must
      //                 be legal.
      // PostConditions: The array entry at the specified index has been
      //                 set to the specified value.
      void SetVal(const unsigned int index, const NumTmpl& value);

      // PreConditions:  None.
      // PostConditions: The value will be added to the container.  If there
      //                 was not room in the container, it's size has doubled.
      void PushBack(const NumTmpl& value);

      // PreConditions:  None.
      // PostConditions: The last value in the array will be removed.
      void PopBack();

      // PreConditions:  None.
      // PostConditions: Returns the number of elements used.
      unsigned int GetUsed() const;

   private:
      // The number of elements used.
      unsigned int used_;

      // The length of the  array.
      unsigned int length_;

      // A pointer to the array.
      NumTmpl * dataPtr_;
};

#include "Array.tpp"

#endif
