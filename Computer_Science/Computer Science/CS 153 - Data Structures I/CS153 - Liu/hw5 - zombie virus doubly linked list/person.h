/* Name: Roberto Murillo
 * Instructor: Liu
 * Date: 2/17/06
 * File: PERSON.h
 * Description: Contains the variables and functions for the PERSON class.
 */

#ifndef PERSON_H
#define PERSON_H

/********* PERSON CLASS *********/

class PERSON
{
  // Member variables
  CString status;
  CString name;

  public:
    /* Constructor
     * Pre: None.
     * Post: name is set to blank and status is set to Unvaccinated
     */
    PERSON() {name = ""; status = "Unvaccinated";}

    /* Constructor
     * Pre: None.
     * Post: name is set to passed value and status is set to Unvaccinated.
     */
    PERSON( CString pName ) {name = pName; status = "Unvaccinated";}

    /* Accessor
     * Pre: None.
     * The name is returned.
     */
    CString getName()const {return name;}

    /* Accessor
     * Pre: None.
     * The status is returned.
     */
    CString getStatus()const {return status;}

    /* Mutator
     * Pre: None.
     * The name is set to the value passed.
     */
    void setName( const CString pName ) {name = pName;}

    /* Mutator
     * Pre: None.
     * The status is set to the value passed.
     */
    void setStatus( const CString pStatus ) {status = pStatus;}

    /* Mutator
     * Pre: None.
     * The status is set to "Vaccinated".
     */
    void setVaccinated(){status = "Vaccinated";}

    /* Mutator
     * Pre: None.
     * The status is set to "Zombie".
     */
    void setZombie() {status = "Zombie";}
};

/********* PERSON CLASS *********/

#endif
