/* programmer: roberto murillo
 * instructor: liu
 * date: 2/6/06
 * file: list.h
 * desc: contains the class definition for the link list.
 */

#ifndef LIST_H
#define LIST_H

#include "node.h"
#include <iostream>
using namespace std;

class LINKLIST
{
  // Member variable.
  NODE* headPtr;

  public:
    /* Constructor
     * Pre: None.
     * Post: headPtr is set to NULL
     */
    LINKLIST();

    /* Destructor
     * Pre: None.
     * Post: All nodes are deleted.
     */
    ~LINKLIST();

    /* Accessor
     * Pre: None.
     * The headPtr is returned.
     */
    NODE* getHeadPtr()const;
    
    /* "Empties" the list. ( Clears NODES )
     * Pre: None.
     * Post: All nodes that remain are deleted.
     */
    void clearContents();

    bool isEmpty();
    
    /* Inserts new node(data) at the head of the list.
     * Pre: The data is a non-negative number <10.
     * Post: The new data is added at the head of the list.
     */
    void insertAtHead( const char & data1 );
    
    /* Removes the head node.
     * Pre: None.
     * Post: The NODE in the GetCurSel position 0 is removed.
     */
    void removeHeadNode();
    
    /* Removes the node that is selected in the ListBox.
     * Pre: GetCurSel must be a number other than -1 because -1 means nothing
     *      is selected.
     * Post: The node in the GetCurSel position that was selected is deleted.
     */
    void removeNode( NODE* ptrToPrevNode);
    
    /* Search function
     * Pre: GetCurSel must be > -1 because -1 means nothing is selected.
     * Post: The NODE in the position returned by GetCurSel is returned.
     */
    NODE* findNodeByIndex( const int index );
};

#endif
