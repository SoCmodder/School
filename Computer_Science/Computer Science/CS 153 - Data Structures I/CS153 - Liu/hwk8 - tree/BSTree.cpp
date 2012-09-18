/* Programmer: Roberto Murillo
 * Date: 3/21/06
 * Instructor: Liu
 * File Description: Contains the function definitions for BSTree class.
 */

#include "stdafx.h"
#include "BSTree.h"

BSTree::~BSTree()
{
  clearTree( getRootForUpdate() );
}

void BSTree::clearTree( NODE* &root1 )
{
  if( root1 != NULL )
  {
    // Deletes all the bottom NODES first and works its way up.
    clearTree( root1->getLeftForUpdate() );
    clearTree( root1->getRightForUpdate() );

    delete root1;
    root1 = NULL;
  }
}

bool BSTree::insert( NODE* &root1, CString arg )
{
	bool placed = false;

  if( root1 == NULL )
  {
    // If nothing is in the node, we can just insert info here.
    NODE* temp = new NODE( arg );
		root1 = temp;
		placed = true;
  }

  else if( arg == root1->getData() )
  {
    // If it is already in the tree, we can increase its count.
    root1->increaseData();
    placed = true;
  }
		
	else if( arg > root1->getData() )
    // If arg is bigger, we go to the right!
		insert( root1->getRightForUpdate(), arg );
		
	else if( arg < root1->getData() )
    // If arg is smaller, we go to the left!
		insert( root1->getLeftForUpdate(), arg );
	
	return placed;
}

NODE* BSTree::find( NODE* root1, CString arg )
{
  NODE* temp = NULL;

  if( root1 != NULL )
  {
    // If arg = getData, then we found it and return it!
    if( arg == root1->getData() )
      temp = root1;

    else if( arg < root1->getData() )
      temp = find( root1->getLeft(), arg );

    else if( arg > root1->getData() )
      temp = find( root1->getRight(), arg );

    else
      temp = NULL;
  }

  return temp;
}

bool BSTree::remove( NODE* &root1, CString arg )
{
  bool removed = false;

  if( root1 == NULL )
    removed = false;

  else if( root1->getData() == arg )
  {
    // If it has no children, we can just remove it.
    if( root1->isLeaf() )
    {
      NODE* temp = root1;
      root1 = NULL;
      delete temp;
      removed = true;
    }

    // If there is no left child, we can just replace it with the right child.
    else if( root1->getLeft() == NULL )
    {
      NODE* temp = NULL;
      temp = root1;
      root1 = root1->getRightForUpdate();
      delete temp;
      removed = true;
    }

    // If it has a left child, we have to get the furthest rightchild 
    // in the left subtree.
    else
    {
      NODE* rootLeftChild = root1->getLeft(); // Root's left child.
      NODE* parentNode = NULL; // Keeps track of the parent.
      
      // Loop goes until it gets furthest to the right.
      while( rootLeftChild->getRightForUpdate() != NULL )
      {
        parentNode = rootLeftChild; // Makes the previous node the current.
        // This is the node we are going to replace root with.
        rootLeftChild = rootLeftChild->getRightForUpdate();
      }

      // Replaces root's data with the furthest right node in the left subtree.
      root1->setCount( rootLeftChild->getCount() );
      root1->setData( rootLeftChild->getData() );

      // If previous is not NULL, then we want to make its right pointer NULL
      // since we removed it and replaced root with it.
      if( parentNode != NULL )
        parentNode->setRight( NULL );

      else
        // Otherwise, we didn't move any, so we set root's left child to NULL.
        root1->setLeft( NULL );

      // Now we delete
      delete rootLeftChild;
      removed = true;
    }
  }

  else if( root1->getData() > arg )
    removed = remove( root1->getLeftForUpdate(), arg );

  else if( root1->getData() < arg )
    removed = remove( root1->getRightForUpdate(), arg );

  return removed;
}

CString BSTree::preOrderTraversal( NODE* root1 )
{
  if( root1 == NULL )
    return "";

  else
  {
    // Adds the NODE to the string first.
    CString preString = root1->toString();
    // Then it adds the Left child.
    preString = preString + ", " + preOrderTraversal( root1->getLeft() );
    // Then it adds the right child.
    preString += preOrderTraversal( root1->getRight() );
    return ( preString );
  }
}

CString BSTree::inOrderTraversal( NODE* root1 )
{
  if( root1 == NULL )
    return "";

  else
  {
    CString inOrdString;
    // Adds the leftchild to the string first.
    inOrdString = inOrderTraversal( root1->getLeft() );
    // Adds the NODE to the string second.
    inOrdString = inOrdString + root1->toString();
    // Adds the rightchild to the string last.
    inOrdString = inOrdString + ", " + inOrderTraversal( root1->getRight() );
    return inOrdString;
  }
}

CString BSTree::postOrderTraversal( NODE* root1 )
{
  if( root1 == NULL )
    return "";

  else
  {
    CString postString;
    // Adds the Leftchild to the string first.
    postString = postOrderTraversal( root1->getLeft() );
    // Adds the rightchild to the string second.
    postString = postString + postOrderTraversal( root1->getRight() );
    // Adds the NODE to the string last.
    postString = postString + root1->toString() + ", ";
    return postString;
  }
}