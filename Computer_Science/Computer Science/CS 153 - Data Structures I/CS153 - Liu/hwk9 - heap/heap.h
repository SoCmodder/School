/* programmer: roberto murillo
 * instructor: liu
 * date: 4/18/06
 * file: heap.h
 * desc: contains the class definition for the HEAP.
 */

#ifndef HEAP_H
#define HEAP_H

#include "patient.h"

class HEAP
{
  int numPatients;
  int capacity;
  PATIENT *patients;

  public:
    /* Constructor
     * Pre: None
     * Post: Variables are assigned default values, and the patients array is
     *       created.
     */
    HEAP();

    /* Copy Constructor
     * Pre: None.
     * Post: All info from the passed heap is copied into the new heap.
     */
    HEAP( HEAP& heapToCopy );

    /* Destructor
     * Pre: None
     * Post: Deletes all used memory.
     */
    ~HEAP();

    /* Accessor Function
     * Pre: None
     * Post: Returns the capacity.
     */
    int getCapacity()const;

    /* Accessor Function
     * Pre: None
     * Post: Returns the number of patients.
     */
    int getNumPatients()const;

    /* Accessor Function
     * Pre: None
     * Post: Returns the PATIENT in the passed int.
     */
    PATIENT getPatient( int numPat )const;

    /* Mutator Function
     * Pre: Number passed must be >= 0
     * Post: numPatients is set to passed number.
     */
    void setNumPatients( int newNum );

    /* Clears the heap.
     * Pre: None.
     * Post: numPatients is set to 0.
     */
    void clear();

    /* Checks to see if the bag is full.
     * Pre: None.
     * Post: If numPatients = capacity, it increases the size.
     */
    bool isFull();

    /* Insertion function.
     * Pre: Must have a priority > -1
     * Post: Inserts the passed patient into the heap, and thensorts it
     *       by priority.
     */
    bool insert( PATIENT patToBeAdded );

    /* Increases size.
     * Pre: numPatients = capacity
     * Post: capacity is increased by 5.
     */
    void increaseRoom();

    /* Removes the root.
     * Pre: None.
     * Post: Root is removed and replaced by next highest priority.
     */
    bool removeRoot();
};

#endif
