// Section 13.4
// $ CC screen.cpp main4.cpp

/*
  ###
  #*#
  ###
  @@@@@###
  @@@@@###
  @@@@@###
  @@@@@###
  @@@@@###
  ########
  ########
  ########
*/

#include "screen.h"

int main() {
        Screen myScreen(3,3,'-'), bufScreen(5,5,'@');

        myScreen.clear().move(2,2).set('*').display();

        bufScreen.reSize(8,8).display();
}

