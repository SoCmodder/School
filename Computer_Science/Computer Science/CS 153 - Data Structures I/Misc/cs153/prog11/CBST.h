//CBST.h
//Erin Pringle and Joe Wingbermuehle
//This class works with a binary search tree.

#ifndef CBST_h

#define CBST_h

// A basic node (must be inherited)
struct BNode
{
	// Constructor
	// PRE: none
	// POST: a new BNode object is created
	BNode(){right=NULL;left=NULL;}

	// Destructor
	// PRE: none
	// POST: destroys the BNode and any derived objects
	virtual ~BNode() { };

	// Comparison functions
	// PRE: right is the BNode to compare to
	// POST: returns 1 if compare true, 0 if false
	virtual bool operator ==(const BNode& right) const=0;
	virtual bool operator >(const BNode& right) const=0;
	virtual bool operator <(const BNode& right) const=0;
	virtual bool operator >=(const BNode& right) const=0;
	virtual bool operator <=(const BNode& right) const=0;

	// Display the node
	// PRE: list is the CListBox in which to display the value
	// POST: displays the value
	virtual void Show(CListBox& list) const=0;

	BNode *left; //next left node pointer
	BNode *right; //next right node pointer
};


class CBST
{
public:

	//Constructor
	//PRE:  none
	//POST:  A new empty tree is created.
	CBST();

	//Destructor
	//PRE:  root is the root pointer of a binary tree
	//POST:  The tree is deleted and the root set to NULL.
	~CBST();

	//Inserts an integer into the tree
	//PRE:  arg is an integer
	//POST:  arg is inserted into the appropriate place in the tree
	bool Insert(BNode *arg);

	//Finds an integer in the tree
	//PRE:  arg is an integer
	//POST:  Returns true if arg is found in the tree, false if 
	//       it is not found.
	bool Find(BNode *arg)const;

	//Displays the tree in order
	//PRE: box is the CListBox in which to display the tree
	//POST:  The tree is displayed in the CListBox box in order.
	void DisplayInOrder(CListBox &box);

	// Display the elements of the tree in pre order
	// PRE: box is the CListBox in which to put the items
	// POST: box holds the items in order
	void DisplayPreOrder(CListBox &box);

	// Display the elements of the tree in post order
	// PRE: box is the CListBox in which to put the items
	// POST: box holds the items in order
	void DisplayPostOrder(CListBox &box);

	// Remove a BNode from the tree
	// PRE: value is the item to remove
	// POST: removes value from the tree (if possible), returns 1 if found
	//       0 if not found
	bool Remove(BNode *value);

	// Remove all items from the tree
	// PRE: none
	// POST: all items are removed from the tree
	void Purge(void);

private:
	BNode *root; //pointer to the root of the binary tree

	//Helper function to the display function
	//PRE: box is the CListBox in which to display the subtree
	//      current points to the subtree
	//POST:  The tree is displayed in the list box in order.
	void DisplayInOrder(CListBox &box, BNode *current);

	//Helper function to the destructor
	//PRE:  root is the root pointer of a binary tree
	//POST:  The tree is deleted and root set to NULL.
	void HelpDestruct(BNode *current);

	// Recursive function fo removing an item from the tree
	// PRE: value points to the value to remove, current is the subtree
	// POST: removes the node from the tree if possible
	//       returns 1 on success, 0 on failure
	bool Remove(BNode *value,BNode *&current);

	// Recursive function for displaying the tree in pre order
	// PRE: list is the CListBox in which to display the subtree
	//      ptr points to the subtree
	// POST: list holds the items in the subtree pointed to by ptr
	void DisplayPreOrder(CListBox &list,BNode *ptr);

	// Recursive function for displaying the tree in post order
	// PRE: list is the CListBox in which to display the subtree
	//      ptr points to the subtree
	// POST: list holds the items in the subtree pointed to by ptr
	void DisplayPostOrder(CListBox &list,BNode *ptr);
};

#endif