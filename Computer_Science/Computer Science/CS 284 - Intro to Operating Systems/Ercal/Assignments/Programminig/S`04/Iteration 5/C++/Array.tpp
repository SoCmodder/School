// Author: Matt Johnson
// FileName: Array.tpp
// Course: CS 328 - Object Oriented Numerical Modeling I
// Instructor: Clayton Price 
// 
// See header file for class description and revision history.
// Current Version is 1.0.

#include <unistd.h>
#include <stdlib.h>

using std::cerr;

template<typename NumTmpl>
Array<NumTmpl>::Array(unsigned int length)
   : used_(0)
   , length_(length)
   , dataPtr_(0)
{
   // Allocate memory for the array.
   dataPtr_ = new NumTmpl[length_];
   used_ = 0;
}

template<typename NumTmpl>
Array<NumTmpl>::Array(const Array & original)
   : length_(original.length_)
   , dataPtr_(0)
{
   unsigned int ii = 0;

   // Allocate memory for the array.
   dataPtr_ = new NumTmpl[length_];

   // Copy data into the new array.
   for(ii = 0; ii < length_; ++ii)
   {
      dataPtr_[ii] = original.dataPtr_[ii];
   }
   used_ = original.used_;
}

template<typename NumTmpl>
Array<NumTmpl>::~Array()
{
   // Release memory back to the operating system.
   if(dataPtr_)
   {
      delete [] dataPtr_;
      dataPtr_ = 0;
      used_ = 0;
      length_ = 0;
   }
}

template<typename NumTmpl>
const Array<NumTmpl>& Array<NumTmpl>::operator=(const Array & original)
{
   unsigned int ii = 0;

   // Release memory back to the operating system.
   if(dataPtr_)
   {
      delete [] dataPtr_;
   }

   length_ = original.length_;
   used_ = original.used_;

   // Allocate memory for the array.
   dataPtr_ = new NumTmpl[length_];

   // Copy data into the new array.
   for(ii = 0; ii < length_; ++ii)
   {
      dataPtr_[ii] = original.dataPtr_[ii];
   }

   return *this;
}

template<typename NumTmpl>
bool Array<NumTmpl>::Clear()
{
   if(dataPtr_)
   {
      delete [] dataPtr_;
      dataPtr_ = 0;
   }
   length_ = 0;
   used_ = 0;
   return true;
}

template<typename NumTmpl>
unsigned int Array<NumTmpl>::GetLength()
{
   return length_;
}

template<typename NumTmpl>
unsigned int Array<NumTmpl>::GetUsed() const
{
   return used_;
}

template<typename NumTmpl>
void Array<NumTmpl>::SetLength(unsigned int newLength)
{
   if(newLength > 0)
   {
      unsigned int ii = 0;
      NumTmpl * tempPtr = new NumTmpl[newLength];
   
      // copy data over into the new memory
      for(ii = 0; (ii < length_ && ii < newLength); ++ii)
      {
         tempPtr[ii] = dataPtr_[ii];
      }
   
      // free up previously used memory
      if(dataPtr_)
      {
         delete [] dataPtr_;
      }

      dataPtr_ = tempPtr;
      length_ = newLength;
   }
   else
   {
      Clear();
   }
}

template<typename NumTmpl>
NumTmpl& Array<NumTmpl>::operator[](const unsigned int &index) const
{
   if(index >= length_)
   {
      cerr << "Array index error Array<NumTmpl>::operator[]" << endl;
      cerr << "Index " << index << " is invalid." << endl;
      cerr << "Program exiting." << endl;
      exit(EXIT_FAILURE);
   }
   return dataPtr_[index];
}

template<typename NumTmpl>
void Array<NumTmpl>::SetVal(const unsigned int index, const NumTmpl& value)
{
   if(index >= length_)
   {
      cerr << "Array index error Array<NumTmpl>::SetVal" << endl;
      cerr << "Program exiting." << endl;
      exit(EXIT_FAILURE);
   }
   dataPtr_[index] = value;

   if(index >= used_)
   {
      used_ = index + 1;
   }
}

template<typename NumTmpl>
void Array<NumTmpl>::PopBack()
{
   if(used_ > 0)
   {
      used_--;
   }
}

template<typename NumTmpl>
void Array<NumTmpl>::PushBack(const NumTmpl& value)
{
   if(used_ < length_)
   {
      SetVal(used_, value);
   }
   else
   {
      if(length_ == 0)
      {
         SetLength(1);
      }
      else
      {
         SetLength(length_ * 2);
      }
      SetVal(used_, value);
   }
}

template<typename NumTmpl>
ostream& operator<<(ostream& ofile, const Array<NumTmpl>& arr)
{
   unsigned int ii = 0;
   for(ii = 0; ii < used_; ++ii)
   {
      ofile << arr[ii] << endl;
   }

   return ofile;
}

template<typename NumTmpl>
istream& operator>>(istream& ifile, Array<NumTmpl>& arr)
{
   std::string temp;

   for(ii = 0; ii < length_ && !ifile.eof() && !ifile.fail(); ++ii)
   {
      ifile >> temp;
      dataPtr_[ii] = static_cast<NumTmpl>(atof(temp.c_str()));
   }
   if(ii != length_)
   {
      cerr << "Problem reading ifile!" << endl;
      cerr << "istream& operator>> <>(istream& ifile, Array<NumTmpl>& arr)" 
         << endl;
      exit(EXIT_FAILURE);
   }

   return ifile;
}
