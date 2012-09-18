/* Programmer: Roberto Murillo
 * Date: 3/21/06
 * Instructor: Liu
 * File Description: Contains the class and function prototypes for 
 *                   BSTree class.
 */

#include "node.h"

#ifndef BSTREE_H
#define BSTREE_H

/********* BINARY SEARCH TREE CLASS *********/

class BSTree
{
  NODE * root;

  public:
    /* Constructor
     * Pre: None.
     * Post: root is set to NULL.
     */
    BSTree() {root = NULL;}

    /* Destructor
     * Pre: None.
     * Post: All extra memory is cleared.
     */
    ~BSTree();

    /* Clears the tree.
     * Pre: None.
     * Post: Every node is deleted freeing up left over memory.
     */
    void clearTree( NODE* &root1 );

    /* Accessor
     * Pre: None.
     * Post: root is returned.
     */
    NODE* getRoot() {return root;}

    /* Accessor
     * Pre: None.
     * Post: root is returned by reference.
     */
    NODE*& getRootForUpdate() {return root;}

    /* Inserts a new item.
     * Pre: None.
     * Post: The value passed is inserted into the tree in alphabetical order.
     */
    bool insert( NODE* &root, CString arg );

    /* Finds the node that includes the passed CString.
     * Pre: None.
     * Post: Returns true if a NODE with given CString is found.
     */
    NODE* find( NODE* root, CString arg );

    /* Removes a NODE with the passed value.
     * Pre: None.
     * Post: root is set to NULL.
     */
    bool remove( NODE* &root, CString arg );

    /* PreOrders the tree.
     * Pre: Tree must have something in it.
     * Post: The data from the nodes are put in preOrder and output to a 
     * result box.
     */
    CString preOrderTraversal( NODE* root1 );

    /* inOrders the tree.
     * Pre: Tree must have something in it.
     * Post: The data from the nodes are put in inOrder and output to a 
     * result box.
     */
    CString inOrderTraversal( NODE* root1 );

    /* PostOrders the tree.
     * Pre: Tree must have something in it.
     * Post: The data from the nodes are put in postOrder and output to a 
     * result box.
     */
    CString postOrderTraversal( NODE* root1 );

    /* Unhooks the max node.
     * Pre: None.
     * Post: Returns the node in the furthest right position (maximum).
     */
    //NODE* Unhook( NODE*& root1 );
};

/********* BINARY SEARCH TREE CLASS *********/

#endif

