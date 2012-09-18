// Section 13.6
// $ CC screen.cpp main6.cpp

/*
  #*#
  ###
  ###
  #*#
  ###
  #@#
*/

#include "screen.h"

int main() {
        Screen myScreen( 3, 3 );

        myScreen.home().move(Screen::FORWARD).set('*').display();

	myScreen.repeat(&Screen::down, 2).set('@').display();

	return 0;
}

