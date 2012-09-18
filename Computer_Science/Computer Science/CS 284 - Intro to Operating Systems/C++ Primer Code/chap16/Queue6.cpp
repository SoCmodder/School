template <class Type>
Queue<Type>::~Queue()
{
        while ( ! is_empty() )
                remove();
}

template <class Type>
void Queue<Type>::add( const Type &val )
{
        // allocate a new QueueItem object
        QueueItem *pt =
                new QueueItem( val );

        if ( is_empty() )
                front = back = pt;
        else
        {
                back->next = pt;
                back = pt;
        }
}

template <class Type>
Type Queue<Type>::remove()
{
        if ( is_empty() )
        {
                cerr << "remove() on empty queue\n";
                exit( -1 );
        }

        QueueItem *pt = front;
        front = front->next;

        Type retval = pt->item;
        delete pt;
        return retval;
}

template <class Type>
ostream& operator<<( ostream &os, const Queue<Type> &q )
{
        os << "< ";
        QueueItem<Type> *p;
        for ( p = q.front; p; p = p->next )
                        os << *p << " ";
        os << " >";
        return os;
}

template <class Type>
ostream& operator<<( ostream &os, const typename Queue<Type>::QueueItem &qi )
{
        os << qi.item;
        return os;
}

template <class T>
        typename Queue<T>::QueueItem *Queue<T>::QueueItem::free_list = 0;

template <class T>
        const unsigned int Queue<T>::QueueItem::QueueItem_chunk = 24;

template <class Type>
        void* Queue<Type>::QueueItem::operator new( size_t size )
{
        QueueItem *p;
        if ( ! free_list )
        {
                size_t chunk = QueueItem_chunk * size;
                free_list = p =
                        reinterpret_cast< QueueItem* >
                                        ( new char[chunk] );

                for ( ; p != &free_list[ QueueItem_chunk - 1 ]; ++p )
                        p->next = p + 1;
                p->next = 0;
        }

        p = free_list;
        free_list = free_list->next;
        return p;
}

template <class Type>
        void Queue<Type>::QueueItem::operator delete( void *p, size_t )
{
        static_cast< QueueItem* >( p )->next = free_list;
        free_list = static_cast< QueueItem* > ( p );
}

