// Program 9 (Peg game solver)
// Erin Pringle and Joe Wingbermuehle
// This is the implementation file for the peg solver routines

#include "stdafx.h"
#include "game.h"
#include <math.h>
#include <stdlib.h>

int boardSize;		// The size of the current board (number of pegs+2)

// board matrix
int board[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];
SMoves moves[MAX_BOARD_SIZE-1];		// move history for the current game

// Get the y-coordinate for a given peg number
// PRE: number is a valid peg position
// POST: returns the y-coordinate (matrix offset) for the peg position
int GetY(int number) {
	int i;	// the number of position on a level
	int y;	// incremented for every level (or y matrix offset)

	for(i=1,y=1;i<number+1;y++,i+=y);
	return y;
}

// Get the x-coordinate for a given peg number
// PRE: number is a valid peg position
// POST: returns the y-coordinate (matrix offset) for the peg position
int GetX(int number) {
	int x;	// counter for the x-coordinate
	int i;	// index, counts up to number
	int limit;	// max number of x values for a level

	// Initialize
	x=0;
	limit=0;

	// Count up to number
	for(i=0;i<number+1;i++) {

		// If the x coordinate is larger than the
		// limit, up the limit and reset the x
		if(x>limit) {
			++limit;
			x=0;
		}
		++x;
	}

	return x;
}

// Get the peg position of an (x,y) pair
// PRE: x is a valid x-coordinate, y is a valid y-coordinate
// POST: returns the peg position for the (x,y) pair
int GetNumber(int x, int y) {
	int a;		// index
	int number;	// the peg position
	int limit;	// the number of x positions on a level

	limit=1;
	number=x;	// Start with x and then apply the y

	// Calculate and add the y position to number
	for(a=1;a<y;a++) {
		number+=limit;
		++limit;
	}
	return number;
}

// Determine if a move is possible
// PRE: from is the peg to move, to is where to put the peg
//       from and to must be on the board
// POST: returns 1 if the move is possible, else returns 0
int CheckMove(int from,int to) {
	int fromX,fromY;	// From coordinates
	int toX,toY;		// To coordinates
	int midX,midY;		// Coordinates of the jumped peg
	int middle;			// Peg position of the jumped peg
	int length;			// Vertical length of the jump

	length=abs(from-to);

	// Calculate the peg to be jumped
	if(to>from) {
		middle=from+(to-from)/2;
	} else {
		middle=to+(from-to)/2;
	}

	// Convert the peg positions to matrix offsets
	fromX=GetX(from);
	fromY=GetY(from);
	toX=GetX(to);
	toY=GetY(to);
	midX=GetX(middle);
	midY=GetY(middle);

	// Is this move possible?
	if(length<2
		|| length>2*GetY(MAX_BOARD_SIZE-2)-1
		|| (abs(fromY-toY)!=2 && GetY(from)-GetY(to))
		|| (abs(fromX-toX)!=2 && fromX-toX)) {
		return 0;
	}

	// Are the pegs arranged correctly?
	if(board[fromX][fromY]!=1
		|| board[toX][toY]!=0
		|| board[midX][midY]!=1) {
		return 0;
	}

	return 1;
}

// Take back a move
// PRE: numberPegs is the number of the move to take back (must be valid)
// POST: reverts the board to its previous condition
void UnMove(int numberPegs) {
	SMoves temp=moves[boardSize-numberPegs-2];

	board[temp.fromX][temp.fromY]=1;
	board[temp.toX][temp.toY]=0;
	board[temp.midX][temp.midY]=1;
}

// Make a move
// PRE: numberPegs is the number of the move to make (must be valid)
// POST: makes a move, updating the board
void DoMove(int numberPegs) {
	SMoves temp=moves[boardSize-numberPegs-2];

	board[temp.fromX][temp.fromY]=0;
	board[temp.toX][temp.toY]=1;
	board[temp.midX][temp.midY]=0;
}

// Solve the puzzle
// PRE: numberPegs is the number of pegs left, must be
//      less then the boardSize-2 and greater than 0
// POST: returns 1 and a solved board (moves/board updated)
//       on success, else returns 0 (and only moves is modified)
int Solve(int numberPegs) {

	// struct to hold possible move offsets
	struct PossibleMoves {
		int midX,midY;		// Offsets to jumped peg
		int toX,toY;		// Offsets to destination
	};

	// Moves to try for each position
	static const PossibleMoves pm[6]={
		{1,0,	2,0},
		{-1,0,	-2,0},
		{0,1,	0,2},
		{0,-1,	0,-2},
		{1,1,	2,2},
		{-1,-1,	-2,-2}
	};

	int x,y,z;		// index variables for looping
	int temp;		// the current from peg position

	// Width/height of the matrix (starting at one and ignoring border)
	static int matrixSize=GetY(boardSize);

	// base case
	if(numberPegs==1) {
		return 1;
	}

	// Loop through the y coordinates
	for(y=1;y<matrixSize+1;y++) {

		// Loop through x coordinates
		for(x=1;x<y+1;x++) {

			// Check that the from location is a peg
			if(board[x][y]==1) {

				// Set the from location
				temp=boardSize-numberPegs-2;
				moves[temp].fromX=x;
				moves[temp].fromY=y;

				// Loop through possible moves
				for(z=0;z<6;z++) {

					// Attempt a move if possible
					if(board[x+pm[z].midX][y+pm[z].midY]==1
						&& !board[x+pm[z].toX][y+pm[z].toY]) {
						moves[temp].toX=x+pm[z].toX;
						moves[temp].toY=y+pm[z].toY;
						moves[temp].midX=x+pm[z].midX;
						moves[temp].midY=y+pm[z].midY;
						DoMove(numberPegs);
						if(Solve(numberPegs-1)) {
							return 1;
						} else {
							UnMove(numberPegs);
						}
					}
				}
			}
		}
	}
	
	return 0;
}


