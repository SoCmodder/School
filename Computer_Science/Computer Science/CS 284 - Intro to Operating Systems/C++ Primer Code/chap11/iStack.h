#ifndef ISTACK_H
#define ISTACK_H

#include <vector>
using std::vector;

#include "stckexcp.h"

class iStack {
public:
        iStack( int capacity )
              : _stack( capacity ), _top( 0 ) { }

        void pop( int &top_value ) throw( popOnEmpty );
        void push( int value ) throw( pushOnFull );

        bool full();
        bool empty();
        void display();

        int size();

private:
        int _top;
        vector< int > _stack;
};

inline int  iStack::size()  { return _top; };
inline bool iStack::empty() { return _top ? false : true; }
inline bool iStack::full()  { return _top < _stack.size()-1 ? false : true; };

#endif
