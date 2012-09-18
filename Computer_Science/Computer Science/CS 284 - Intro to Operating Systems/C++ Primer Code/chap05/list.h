#ifndef list_h_
#define list_h_

#include <iostream.h>

template <class elemType>
class list_item {
public:
    list_item( elemType value, list_item *item_to_link_to = 0 );

    elemType    value() const             { return _value; }
    void        value( const elemType& et){ _value = et;   }

    void        next( list_item *link )   { _next = link;  }
    list_item*  next()                    { return _next;  }

private:
    elemType   _value;
    list_item *_next;
};

template <class elemType>
inline 
list_item<elemType>::
list_item( elemType value, list_item *item ) 
	   : _value( value )
{
    if ( ! item )
	 _next = 0;
    else {
	 _next = item->_next;
	 item->_next = this;
    }
}

template <class elemType>
class list {
public:
    list() : _at_front( 0 ), _at_end( 0 ), _current( 0 ), _size( 0 ) {}
    ~list() { remove_all(); }

    void insert( list_item<elemType> *ptr, elemType value );

    void insert_end( elemType value );
    void insert_front( elemType val );

    int  remove( list_item<elemType> *ptr );
    int  remove( elemType value );

    void remove_front();
    void remove_all();

    list_item<elemType> *find( elemType value );
    list_item<elemType> *next_iter();  
    list_item<elemType> *init_iter() { return _current = _at_front; }

    void display();

    void concat( const list& );
    void reverse();

    list concat_copy( const list& ) const;
    list reverse_copy() const;

    int size() { return _size; }

private:
    void bump_up()   { ++_size; }
    void bump_down() { --_size; }

    list( const list& );
    list& operator=( const list& );

    list_item< elemType > *_at_front;
    list_item< elemType > *_at_end;
    list_item< elemType > *_current;
    int _size;
};

template< class elemType >
inline list_item<elemType>*
list<elemType>::
next_iter() 
{ 
    list_item<elemType> *next = _current 
			? _current = _current->next() 
			: _current; 

    if ( ! _current )
	   _current = _at_front;

    return next;
}

template< class elemType> 
inline void
list<elemType>::
remove_front()
{
    
    if ( _at_front ) {
         list_item<elemType> *ptr = _at_front;
	 _at_front = _at_front->next();

         // don't want current to point to a deleted item
	 if ( _current == ptr )
	      _current = _at_front;

	 bump_down();
	 delete ptr;
    }
}

template< class elemType> 
inline void
list<elemType>::
insert_front( elemType value )
{
    list_item<elemType> *ptr = new list_item<elemType>( value );
    
    if ( ! _at_front ) 
	 _at_front = _at_end = ptr;
    else 
    {
	 ptr->next( _at_front );
	 _at_front = ptr;
    }
  
    bump_up();
}

template< class elemType> 
inline void 
list<elemType>::
insert( list_item<elemType> *ptr, elemType value )
{ 
    if ( ! ptr ) 
  	 insert_front( value );
    else {
	 bump_up();
	 new list_item<elemType>( value, ptr );
    }
}

template< class elemType> 
inline void
list<elemType>::
insert_end( elemType value )
{
    if ( ! _at_end ) 
	 _at_end = _at_front = new list_item<elemType>( value );
    else _at_end = new list_item<elemType>( value, _at_end );
  
    bump_up();
}

#endif
