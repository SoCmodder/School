#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
using std::cerr;
using std::cout;
using std::ostream;

#include <cstdlib>
using std::exit;

// QueueItem is now a nested type of the template Queue

template <class Type>
class Queue {
public:
        Queue() : front( 0 ), back ( 0 ) { }
        ~Queue();

        Type remove();
        void add( const Type & );
        bool is_empty() const {
                return front == 0;
        }

	friend ostream& operator<<( ostream &, const Queue<Type> & );
private:
	class QueueItem {
	        QueueItem( const Type &t )
        	         : item(t), next(0) { }

		friend class Queue<Type>;
	        friend ostream& operator<<( ostream &, 
                                            const QueueItem & );

	        Type item;
	        QueueItem *next;

	        void *operator new( size_t );
	        void operator delete( void *, size_t );

	        static QueueItem *free_list;
	        static const unsigned QueueItem_chunk;
	};

        QueueItem *front;
        QueueItem *back;
};

#endif
