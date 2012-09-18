// Program 9 (Peg game solver)
// Erin Pringle and Joe Wingbermuehle
// This is the header file for the peg solver routines

#ifndef GAME_H
#define GAME_H

// struct to keep track of a move
struct SMoves {
	int fromX,fromY;		// From coordinates
	int toX,toY;			// To coordinates
	int midX, midY;			// Coordinates of the jumped peg
};

const int MAX_BOARD_SIZE=22;	// max number of pegs +2
const int MAX_MATRIX_SIZE=6+2;	// max size of the matrix (max width+2)

extern int boardSize;	// size of the current board (number of pegs+2)

// board matrix
extern int board[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];
extern SMoves moves[MAX_BOARD_SIZE-1];	// move history for the current game

// Determine if a move is possible
// PRE: from is the peg to move, to is where to put the peg
//       from and to must be on the board
// POST: returns 1 if the move is possible, else returns 0
int CheckMove(int from, int to);

// Solve the puzzle
// PRE: numberPegs is the number of pegs left, must be
//      less then the boardSize-2 and greater than 0
// POST: returns 1 and a solved board (moves/board updated)
//       on success, else returns 0 (and only moves is modified)
int Solve(int numberPegs);

// Take back a move
// PRE: numberPegs is the number of the move to take back (must be valid)
// POST: reverts the board to its previous condition
void UnMove(int numberPegs);

// Make a move
// PRE: numberPegs is the number of the move to make (must be valid)
// POST: makes a move, updating the board
void DoMove(int numberPegs);

// Get the x-coordinate for a given peg number
// PRE: number is a valid peg position
// POST: returns the x-coordinate (matrix offset) for the peg position
int GetX(int number);

// Get the y-coordinate for a given peg number
// PRE: number is a valid peg position
// POST: returns the y-coordinate (matrix offset) for the peg position
int GetY(int number);

// Get the peg position of an (x,y) offset
// PRE: x is a valid x-coordinate, y is a valid y-coordinate
//      (to the peg matrix, board)
// POST: returns the peg position for the (x,y) pair
int GetNumber(int x, int y);

#endif