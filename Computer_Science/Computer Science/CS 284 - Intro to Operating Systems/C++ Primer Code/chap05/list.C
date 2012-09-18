#include "list.h"

template <class elemType>
void
list<elemType>::
display()
{
    cout << "\n( " << _size << " )( "; 

    list_item<elemType> *ptr = _at_front;
    while ( ptr ) {
	    cout << ptr->value() << " ";
            ptr = ptr->next();
    }
   
    cout << ")\n";
}

template <class elemType>
list_item<elemType>*
list<elemType>::
find( elemType value )
{
    list_item<elemType> *ptr = _at_front;
    while ( ptr ) 
    {
	    if ( ptr->value() == value )
		 break; 

            ptr = ptr->next();
    }
   
    return ptr;
}

template <class elemType>
void
list<elemType>::
remove_all()
{
    while ( _at_front ) 
	    remove_front();
   
    _size = 0;
    _at_front = _at_end = _current = 0;
}

template <class elemType>
int 
list<elemType>::
remove( elemType value )
{
    list_item<elemType> *plist = _at_front;
    int elem_cnt = 0;

    while ( plist && plist->value() == value ) 
    {
	plist = plist->next();
	remove_front();
	++elem_cnt; 
    }

    if ( ! plist )
	 return elem_cnt;
	
    list_item<elemType> *prev = plist;
    plist = plist->next();

    while ( plist ) 
    {
	if ( plist->value() == value )
	{
	     prev->next( plist->next() );

	     if ( _current == plist )
		  _current = prev->next();

	     delete plist;
	     ++elem_cnt;
             bump_down();
	     plist = prev->next();
	     if ( ! plist ) 
	     {
		  _at_end = prev;
		  return elem_cnt;
	     }
        } 
        else 
        {
	    prev = plist;
	    plist = plist->next();
        }
    }
 
    return elem_cnt;
}

template <class elemType>
void
list<elemType>::
concat( const list &il )
{
	list_item<elemType> *ptr = il._at_front;
	while ( ptr ) {
		insert_end( ptr->value() );
		ptr = ptr->next();
	}
}

template <class elemType>
void 
list<elemType>::
reverse()
{
    list_item<elemType> *ptr = _at_front;
    list_item<elemType> *prev = 0;

    _at_front = _at_end;
    _at_end = ptr;

    while ( ptr != _at_front ) 
    {
	list_item<elemType> *tmp = ptr->next();
	ptr->next( prev );
	prev = ptr;
	ptr = tmp;
    }

    _at_front->next( prev );
}
