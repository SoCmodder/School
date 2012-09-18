#include "IntArray.h"

class PeekbackStack : public IntArray {
private:
	// const int static bos = -1;
	const int static bos;
public:
	// explicit PeekbackStack( int size )
	PeekbackStack( int size ) : IntArray( size ), _top( bos ) {}

	bool empty() const { return _top == bos; }
	bool full()  const { return _top == size()-1; }
	int  top()   const { return _top; }

	int pop() {
 		if ( empty() ) /* handle error condition */ ;
 		return _ia[ _top-- ];
	}

	void push( int value ) {
 		if ( full() ) /* handle error condition */ ;
 		_ia[ ++_top ] = value;
	}

	bool peekback( int index, int &value ) const;

private:
	 int _top;
};

inline bool
PeekbackStack::
peekback( int index, int &value ) const
{
	if ( empty() ) /* handle error condition */ ;

 	if ( index < 0 || index > _top ) {
  		value = _ia[ _top ];
  		return false;
	}

	value = _ia[ index ];
 	return true;
}
