//Matt Ludwikosky
//October 8th
//CS53
//Simple Blackjack program

#include <iostream>
using namespace std;

#include <ctime>   // Contains function 'time' used by random number generator
#include <cstdlib> // Contains functions 'srand' and 'rand'

// Function declarations need to go here...
  int drawCard();
  int hitMe();
  int computeCardTotal(int card1, int card2, int card3, 
				  	   int card4, int card5);
  char cardSymbol(int card);
  bool isOver21(int card1, int card2, int card3, int card4, int card5);
  bool dealerMustStand(int card1, int card2, int card3, int card4, int card5);
  char displayHit();

/*******************************************************************************
Function name: drawCard

Description:   Assign a random value from 1..13 representing a card.

Parameters:    None

Returns:       (int) value from 1..13 representing a card.
*******************************************************************************/
int drawCard()
{
  int card;

  card = 1 + rand() % 13;
  return(card);
}

/*******************************************************************************
Function name: hitMe

Description:   Draw another card (if the user wants another card).

Parameters:    None

Returns:       (int) representation of a card (A = 1, J = 11, Q = 12, K = 13);
                 return 0 if user didn't want another card.
*******************************************************************************/
int hitMe() 
{
  return(drawCard());
}

/*******************************************************************************
Function name: computeCardTotal

Description:   Compute the total for the specified cards. If one of the cards 
               was an ace, count it as 11 instead of 1.

Parameters:    (int) card1..card5 are the representations of 5 cards.

Returns:       (int) total for the hand.
*******************************************************************************/
int computeCardTotal(int card1, int card2, int card3, 
					 int card4, int card5) 
{
  int total=0;

  if(card1 < 10)
	  total += card1;
  else if(card1 > 9)
      total += 10;

  if(card2 < 10)
	  total += card2;
  else if(card2 > 9)
	  total += 10;

  if(card3 < 10)
	  total += card3;
  else if(card3 > 9)
	  total += 10;

  if(card4 < 10)
	  total += card4;
  else if(card4 > 9)
	  total += 10;

  if(card5 < 10)
	  total += card5;
  else if(card5 > 9)
	  total += 10;

  return(total);
}

/*******************************************************************************
Function name: outputHandAndTotal

Description:   Output the specified hand using 'J' for jack, 'Q' for queen,
               'K' for king, 'A' for ace.

Parameters:    (int) card1..card5 are the representations of 5 cards.
               (bool) isPlayer is true if this is the player's hand; otherwise,
			     it is the dealer's hand.

Returns:       Nothing.
*******************************************************************************/
void outputHandAndTotal(int card1, int card2, int card3, 
						int card4, int card5, bool isPlayer) 
{
  if(isPlayer == true)
	  cout << "\n\nPlayer's ";
  else
	  cout << "\n\nDealer's ";

  cout << "hand is (" << cardSymbol(card1) << "," << cardSymbol(card2) << "," 
	   << cardSymbol(card3) << "," << cardSymbol(card4) << "," << cardSymbol(card5) 
	   << ")  total is " << computeCardTotal(card1, card2, card3, card4, card5);
}

/*******************************************************************************
Function name: cardSymbol

Description:   Returns symbol based on card value

Parameters:    (int) card is the card passed to function

Returns:       (char) symbol for the card
*******************************************************************************/
char cardSymbol(int card)
{
  char temp = ' ';

  if(card != 0)
  {
    if(card == 1)
	  return('A');
    else if(card > 1 && card < 10)
    {
	  switch(card)
	  {
	    case 2:
			temp = '2';
			break;
	    case 3:
			temp = '3';
			break;
		case 4:
			temp = '4';
			break;
		case 5:
			temp = '5';
			break;
		case 6:
			temp = '6';
			break;
		case 7:
			temp = '7';
			break;
		case 8:
			temp = '8';
			break;
		case 9:
			temp = '9';
			break;
	  }
	} else if(card == 10)
      temp = 'T';
    else if(card == 11)
      temp = 'J';
    else if(card == 12)
      temp = 'Q';
    else if(card == 13)
      temp = 'K';
    else
      temp = ' ';
  }

  return(temp);
}

/*******************************************************************************
Function name: isOver21

Description:   Determine if the specified hand is over 21.

Parameters:    (int) card1..card5 are the representations of 5 cards.

Returns:       true if specified hand is over 21; otherwise, false.
*******************************************************************************/
bool isOver21(int card1, int card2, int card3, int card4, int card5) 
{
  if((card1 + card2 + card3 + card4 + card5) > 21)
	  return(true);
  else
	  return(false);
}

/*******************************************************************************
Function name: dealerMustStand

Description:   Determine if the specified hand is >= 17.

Parameters:    (int) card1..card5 are the representations of 5 cards.

Returns:       true if specified hand is >= 17; otherwise, false.
*******************************************************************************/
bool dealerMustStand(int card1, int card2, int card3, int card4, int card5) 
{
  if((card1 + card2 + card3 + card4 + card5) >= 17)
	  return(true);
  else
	  return(false);
}

/*******************************************************************************
Function name: displayHit

Description:   Outputs and takes the choice to hit again

Parameters:    none

Returns:       (char) for whether to hit or not.
*******************************************************************************/
char displayHit()
{
	char hit;

	cout << "\nHit (Y/N):";
    cin >> hit;

	while(hit != 'Y' && hit != 'y' && hit != 'N' && hit != 'n')
    {  
	  cout << "\nNo (Y/N): ";
	  cin >> hit;
	}

	return(hit);
}

// Program execution begins here
int main()
{
// You need to put some variable declarations here!!!
  int card1, card2, card3, card4, card5, playerCardTotal, dealerCardTotal;
  bool playerOver21, dealerOver21;
  char playAgain, hit;

  srand(time(0)); // Seed random number generator using current time

  do {

	playerOver21 = false; dealerOver21 = false;
	card3 = 0; card4 = 0; card5 = 0;
	// Get player's initial hand of 2 cards
	card1 = drawCard();
	card2 = drawCard();

	outputHandAndTotal(card1, card2, card3, card4, card5, true);

	hit = displayHit();

	// Player can get at most 3 more cards
	if(hit == 'y' || hit == 'Y')
	  card3 = hitMe();

	if (card3 != 0) {
	  outputHandAndTotal(card1, card2, card3, card4, card5, true);
	  if (! isOver21(card1, card2, card3, card4, card5))
	  {
	    hit = displayHit();
		if(hit == 'y' || hit == 'Y')
	      card4 = hitMe();
	  } else
          playerOver21 = true;
	  if (card4 != 0) {
	    outputHandAndTotal(card1, card2, card3, card4, card5, true);
	    if (! isOver21(card1, card2, card3, card4, card5))
		{
	      hit = displayHit();
		  if(hit == 'y' || hit == 'Y')
	        card5 = hitMe();
		} else
          playerOver21 = true;
		if (card5 != 0) {
	      outputHandAndTotal(card1, card2, card3, card4, card5, true);
		}
	  }
    }

    playerCardTotal = computeCardTotal(card1, card2, card3, card4, card5);
	playerOver21 = isOver21(card1, card2, card3, card4, card5);
	if(playerOver21 == true)
		cout << "\n\nBUST!\n\n";
	// Get dealer's hand
	card1 = drawCard(); card2 = drawCard(); 
	card3 = 0; card4 = 0; card5 = 0;
	// Dealer can get at most 3 more cards, but doesn't have to take any more
	// cards to win if player went over 21
	if (! playerOver21) {
	  if (computeCardTotal(card1, card2, card3, card4, card5) < 17) {
	    card3 = drawCard();
        if ((! isOver21(card1, card2, card3, card4, card5)) &&
			(! dealerMustStand(card1, card2, card3, card4, card5))) {
	      card4 = drawCard();
		  if ((! isOver21(card1, card2, card3, card4, card5)) &&
			  (! dealerMustStand(card1, card2, card3, card4, card5)))
	        card5 = drawCard();
		}
	  }
	}
	outputHandAndTotal(card1, card2, card3, card4, card5, false);

    dealerCardTotal = computeCardTotal(card1, card2, card3, card4, card5);
    dealerOver21 = isOver21(card1, card2, card3, card4, card5);

	cout << "\n\nPlayer Total: " << playerCardTotal;
	cout << "\n\nDealer Total: " << dealerCardTotal;
    cout << "\n\nplayerOver21: " << playerOver21;
	cout << "\n\ndealerOver21: " << dealerOver21;

	if(playerOver21 == false && dealerOver21 == true)
		cout << "\n\nPlayer Wins!\n\n";
	if(playerOver21 == true && dealerOver21 == false)
		cout << "\n\nDealer Wins!\n\n";
	if(playerOver21 == true && dealerOver21 == true)
		cout << "\n\nPush!\n\n";
	if(playerOver21 == false && dealerOver21 == false)
	{
		if(playerCardTotal > dealerCardTotal)
			cout << "\n\nPlayer Wins!\n\n";
		else if(playerCardTotal < dealerCardTotal)
			cout << "\n\nDealer Wins!\n\n";
    }

	// See if player wants to play again
    cout << "\nDo you want to play again? (Y/N) ";
	cin >> playAgain;

  } while ((playAgain == 'Y') || (playAgain == 'y'));

  return 0;
}