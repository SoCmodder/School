/* programmer: roberto murillo
 * instructor: liu
 * date: 4/18/06
 * file: PATIENT.h
 * desc: contains the class definition for the PATIENT.
 */

#ifndef PATIENT_H
#define PATIENT_H

class PATIENT
{
  // Member variables
  CString description;
  int priority;

  public:
    /* Default constructor.
     * Pre: None.
     * Post: Description is set to "" and priority is set to 0.
     */
    PATIENT() {description = ""; priority = 0;}

    /* Overloaded constructor.
     * Pre: None.
     * Post: data passed is set to the PATIENT's desc, and priority is set to
     * the order passed.
     */
    PATIENT( CString initData, int order ) { description = initData; 
             priority = order;}

    /* Accesses the description variable.
     * Pre: None.
     * Post: The description is returned.
     */
    CString getDesc()const {return description;}

    /* Accesses the priority variable.
     * Pre: None.
     * Post: The priority is returned.
     */
    int getPriority()const {return priority;}

    /* Mutator function.
     * Pre: None.
     * Post: The priority is set to the number passed.
     */
    void setPriority( int number ) {priority = number;}

    /* Mutator function.
     * Pre: None.
     * Post: Values from desc passed are given to the PATIENT's description.
     */
    void setDesc( const CString data1 ) {description = data1;}

    /* Adds desc and priority together.
     * Pre: None.
     * Post: Priority is changed to a CString and then added to the desc 
     * variable and then returned.
     */
    CString toString()const;
};

#endif

