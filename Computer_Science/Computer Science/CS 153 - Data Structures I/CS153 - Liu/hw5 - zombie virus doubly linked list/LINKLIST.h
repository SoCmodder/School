/* Name: Roberto Murillo
 * Instructor: Liu
 * Date: 2/17/06
 * File: LINKLIST.h
 * Description: Contains the variables and functions for the LINKLIST class.
 */

#ifndef LINKLIST_H
#define LINKLIST_H

#include "node.h"

/********* LINKLIST CLASS *********/

class LINKLIST
{
    NODE* headPtr;
    NODE* tailPtr;

    public:
    /* Constructor
     * Pre: None.
     * Post: headPtr & tailPtr are set to NULL
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

    /* Accessor
     * Pre: None.
     * The tailPtr is returned.
     */
    NODE* getTailPtr()const;

    /* Mutator
     * Pre: None.
     * The headPtr is set to the value passed.
     */
    void setHeadPtr( NODE* newHeadPtr );

    /* Mutator
     * Pre: None.
     * The tailPtr is set to the value passed.
     */
    void setTailPtr( NODE* newTailPtr );
    
    /* "Empties" the linklist. ( Clears NODES )
     * Pre: None.
     * Post: All nodes that remain are deleted.
     */
    void clearContents();
    
    /* Inserts new node(person) at the head of the list.
     * Pre: None.
     * Post: The new person is added at the head of the list.
     */
    void insertAtHead( const PERSON & human1 );

    /* Inserts new node(person) at the tail of the list.
     * Pre: None.
     * Post: The new person is added at the tail of the list.
     */
    void insertAtTail( const PERSON & human1 );
    
    /* Removes the head node.
     * Pre: None.
     * Post: The NODE in the GetCurSel position 0 is removed.
     */
    void removeHeadNode();

    /* Removes the tail node.
     * Pre: None.
     * Post: The NODE in the last position of the list is removed.
     */
    void removeTailNode();

    /* Removes the passed node.
     * Pre: None.
     * Post: The NODE that is passed is deleted.
     */
    void removeNode( NODE* removedNode );
    
    /* Search function
     * Pre: GetCurSel must be > -1 because -1 means nothing is selected.
     * Post: The NODE in the position returned by GetCurSel is returned.
     */
    NODE* findNodeByIndex( const int index );

    /* Updates the ListBox
     * Pre: None.
     * Post: The ListBox is updated with all current NODES (people).
     */
    void updateBagContentsDisplay( CListBox & listBoxControl );
};

#endif
