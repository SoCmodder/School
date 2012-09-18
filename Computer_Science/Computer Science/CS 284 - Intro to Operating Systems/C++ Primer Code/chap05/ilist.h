#ifndef list_h_
#define list_h_

#include <iostream.h>

class ilist_item {
public:
    ilist_item( int value, ilist_item *item_to_link_to = 0 );

    int         value() const            { return _value; }
    void        next( ilist_item *link ) { _next = link;  }
    ilist_item* next()                   { return _next;  }

private:
    int        _value;
    ilist_item *_next;
};

inline 
ilist_item::
ilist_item( int value, ilist_item *item ) 
	   : _value( value )
{
    if ( !item )
	 _next = 0;
    else {
	 _next = item->_next;
	 item->_next = this;
    }
}

class ilist {
public:
    ilist() : _at_front( 0 ), _at_end( 0 ), _current( 0 ), _size( 0 ) {}
    ilist( const ilist &rhs ) : 
	  _at_front( 0 ), _at_end( 0 ), _current( 0 ) { insert_all( rhs ); }
    ilist& operator=( const ilist &rhs ) { 
	   remove_all(); insert_all( rhs ); return *this;
    }
    ~ilist() { remove_all(); }

    void insert( ilist_item *ptr, int value );

    void insert_all( const ilist &rhs );
    void insert_end( int value );
    void insert_front( int value );

    int  remove( ilist_item *ptr );
    int  remove( int value );
    void remove_front();
    void remove_all();

    ilist_item *find( int value );
    ilist_item *next_iter();  
    ilist_item *init_iter() { return _current = _at_front; }

    void display( ostream& = cout );

    void concat( const ilist& );
    void reverse();

    ilist concat_copy( const ilist& ) const;
    ilist reverse_copy() const;

    int size() { return _size; }

private:
    void bump_up()   { ++_size; }
    void bump_down() { --_size; }

    ilist_item *_at_front;
    ilist_item *_at_end;
    ilist_item *_current;
    int         _size;
};

inline ilist_item*
ilist::
next_iter() 
{ 
    ilist_item *next = _current 
			? _current = _current->next() 
			: _current; 

    if ( ! _current )
	   _current = _at_front;

    return next;
}

inline void
ilist::
remove_front()
{
    
    if ( _at_front ) {
         ilist_item *ptr = _at_front;
	 _at_front = _at_front->next();

         // don't want current to point to a deleted item
	 if ( _current == ptr )
	      _current = _at_front;

	 bump_down();
	 delete ptr;
    }
}

inline void
ilist::
insert_front( int value )
{
    ilist_item *ptr = new ilist_item( value );
    
    if ( !_at_front ) 
	 _at_front = _at_end = ptr;
    else 
    {
	 ptr->next( _at_front );
	 _at_front = ptr;
    }
  
    bump_up();
}

inline void 
ilist::
insert( ilist_item *ptr, int value )
{ 
    if ( !ptr ) 
  	 insert_front( value );
    else {
	 bump_up();
	 new ilist_item( value, ptr );
    }
}

inline void
ilist::
insert_end( int value )
{
    if ( !_at_end ) 
	 _at_end = _at_front = new ilist_item( value );
    else _at_end = new ilist_item( value, _at_end );
  
    bump_up();
}

#endif
