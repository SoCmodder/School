/* programmer: robertoMurillo
 * date: 1/20/06
 * class cs153
 * professor: Liu
 * grocery item header file - contains the class definition for 
 * a grocery item.
 */

#ifndef GROCERY_H
#define GROCERY_H

class GroceryItem
{
	public:
    /* Constructor
     * Pre: None.
     * Post: The description is set to " " and the price is set to 0.
     */		 
     GroceryItem();

    /********* ACCESSOR FUNCTIONS *********/
    /* getDescription() simply returns the description.
     * Pre: Description has been declared.
     * Post: Description is returned to the calling item.
     */
		CString getDescription()const;
		
    /* getPrice() gets the price.
     * Pre: Price has been declared.
     * Post: Price is returned to the calling item.
     */
    double getPrice()const;
    /********* ACCESSOR FUNCTIONS *********/

    /********* MUTATOR FUNCTIONS *********/
    /* setDescription sets the description.
     * Pre: None.
     * Post: Assigns the description passed to the description variable.
     */
    void setDescription( CString desc1 );
		
    /* setPrice sets a price.
     * Pre: The double passed must be a non-negative number because you
     *      cannot have a negative price.
     * Post: Assigns the price passed to the price variable.
     */
    void setPrice( double price1 );
    /********* MUTATOR FUNCTIONS *********/

    /* Converts the price to a CString.
    * Pre: Price that it is converting to a CString must be a non-negative number.
    *      You cannot have a negative price.
    * Post: Convers and the price to a string and concatinates it with the description.
    *       Then it returns the concatination.
    */
    CString toString()const;

	  // member variables
		CString description;
		double price;
};

#endif
