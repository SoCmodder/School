/* Programmer: Roberto Murillo
 * Date: 3/10/06
 * Program Description: This program solves the Queens problem for the N number
 * of queens passed to the program by using recursion.
 * File: queens_class.cpp
 * File Description: Contains the Queens class prototypes.
 * Instructor: Liu
 */

class Queens
{
  int boardSIZE;
  int **board;

  public:
    /* Constructor
     * Pre: The size must be a non-negative integer.
     * Post: Sets the boardSIZE to the size passed, and creates
     *       the 2D chessboard.
     */
    Queens( const int size );
    
    /* Destructor
     * Pre: None.
     * Post: All memory not being used anymore is deleted using clearBoard().
     */
    ~Queens();

    /* Accessor
     * Pre: None.
     * Post: Returns the size of the board.
     */
    int getBoardSize()const {return boardSIZE;}

    /* Mutator
     * Pre: None.
     * Post: Sets the size of the board to the passed size.
     */
    void setBoardSize( int newSize ) {boardSIZE = newSize;}

    /* clearBoard()
     * Pre: None.
     * Post: All memory not being used is deleted.
     */
    void clearBoard();

    /* Display function.
     * Pre: None.
     * Post: Displays the board to the screen.
     */
    void displayBoard();

    /* isUnderAttack( --, -- )
     * Pre: column and row must be non-negative numbers.
     * Post: Returns true if the current position is under attack from the upper
     * left diagnol, lower left diagnol, and horizontally.
     */
    bool isUnderAttack( int column, int row );

    /* place Queens( -- )
     * Pre: currColumn must be a non-negative number.
     * Post: Places a queen as long as the position is not under attack.
     * It does this recursively until all queens have been placed, or no
     * solution is present.
     */
    bool placeQueens( int currColumn );
};