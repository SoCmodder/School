/* programmer: roberto murillo
 * instructor: liu
 * date: 2/6/06
 * file: node.h
 * desc: contains the class definition for the node.
 */

#ifndef NODE_H
#define NODE_H

class NODE
{
  // Member variables
  CString data;
  int count;
  NODE *leftchild;
  NODE *rightchild;

  public:
    /* Default constructor.
     * Pre: None.
     * Post: left and right are set to NULL.  Data is set to "" and count is 
     * set to 0.
     */
    NODE() {data = ""; count = 1; leftchild = NULL; rightchild = NULL;}

    /* Overloaded constructor.
     * Pre: None.
     * Post: data passed is set to the NODE's data, and children are pointed
     *       toward what initLeft/initRight are pointing to.
     */
    NODE( CString initData ) { data = initData; count = 1; leftchild = NULL; 
          rightchild = NULL;}
    
    /* Accesses the left child.
     * Pre: None.
     * Post: Returns the left child.
     */
    NODE* getLeft()const {return leftchild;}

    /* Accesses the left child.
     * Pre: None.
     * Post: Returns the left child.
     */
    NODE*& getLeftForUpdate() {return leftchild;}

    /* Increases data in NODE.
     * Pre: None.
     * Post: count is increased by one.
     */
    void increaseData() {count++;}

    /* Accesses the left child.
     * Pre: None.
     * Post: Returns the left child.
     */
    NODE* getRight()const {return rightchild;}

    /* Accesses the left child.
     * Pre: None.
     * Post: Returns the left child.
     */
    NODE*& getRightForUpdate() {return rightchild;}

    /* Accesses the data variable.
     * Pre: None.
     * Post: The data is returned.
     */
    CString getData()const {return data;}

    /* Accesses the count variable.
     * Pre: None.
     * Post: The count is returned.
     */
    int getCount()const {return count;}

    /* Mutator function.
     * Pre: None.
     * Post: The count is set to the number passed.
     */
    void setCount( int number ) {count = number;}

    /* Mutator function.
     * Pre: None.
     * Post: The leftchild is pointed toward what newLink is pointing at.
     */
    void setLeft( NODE* newLink ) {leftchild = newLink;}

    /* Mutator function.
     * Pre: None.
     * Post: The rightchild is pointed toward what newLink is pointing at.
     */
    void setRight( NODE* newLink ) {rightchild = newLink;}

    /* Mutator function.
     * Pre: None.
     * Post: Values from data passed are given to the NODE's data.
     */
    void setData( const CString data1 ) {data = data1;}

    /* Checks to see if the node is a leaf.
     * Pre: None.
     * Post: If it has no children, it returns true, otherwise it returns 
     * false.
     */
    bool isLeaf()const {return((leftchild == NULL) && (rightchild == NULL));}

    /* Adds data and count together.
     * Pre: None.
     * Post: Count is changed to a CString and then added to the data variable
     * and then returned.
     */
    CString toString()const;
};

#endif

