#include "Array.h"

template <class elemType>
    void try_array( Array<elemType> &iA )
{
    cout << "try_array: initial array values:\n";
    cout << iA << endl;

    elemType find_val = iA [ iA.size()-1 ];
    iA[ iA.size()-1 ] = iA.min();
    int mid = iA.size()/2;

    iA[0] = iA.max();
    iA[mid] = iA[0];

    cout << "try_array: after assignments:\n";
    cout << iA << endl;

    Array<elemType> iA2 = iA;
    iA2[mid/2] = iA2[mid];

    cout << "try_array: memberwise initialization\n";
    cout << iA << endl;

    iA = iA2;
    cout << "try_array: after memberwise copy\n";
    cout << iA << endl;

    iA.grow();
    cout << "try_array: after grow\n";
    cout << iA << endl;

    int index = iA.find( find_val );
    cout << "value to find: " << find_val;
    cout << "\tindex returned: " << index << endl;

    elemType value = iA[index];
    cout << "value found at index: ";
    cout << value << endl;
}
