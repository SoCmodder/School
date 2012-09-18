#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct teamInfo {
 // Define fields here...
};

// Function declarations should go here...


/****************************************************************************
Function name: getTeamCity

Description:   Read in a team's city. (Assume city may have spaces in it.)

Parameters:    None

Returns:       (string) city
****************************************************************************/
string getTeamCity() {

}

/****************************************************************************
Function name: getTeamName

Description:   Read in a team name. (Assume name has no spaces in it.)

Parameters:    None

Returns:       (string) name
****************************************************************************/
string getTeamName() {

}

/****************************************************************************
Function name: getTeamInfo

Description:   Get input for a team's information.

Parameters:    None

Returns:       teamInfo struct.
****************************************************************************/
teamInfo getTeamInfo() {

}

/****************************************************************************
Function name: calculatePowerRanking

Description:   Compute the given team's power ranking.

Parameters:    teamInfo struct team

Returns:       (float) power ranking.
****************************************************************************/
float calculatePowerRanking(const teamInfo team) {

}

/****************************************************************************
Function name: predictGameOutcome

Description:   Output the home and visiting teams' power rankings, and
               make a prediction for the outcome of the game.

Parameters:    teamInfo struct homeTeam
			   teamInfo struct visitingTeam

Returns:       Nothing.
****************************************************************************/
void predictGameOutcome(const teamInfo homeTeam, const teamInfo visitingTeam) {

}

/****************************************************************************
Function name: getInfoForTeams

Description:   Prompt user to enter information for the 2 teams.

Parameters:    teamInfo struct homeTeam
			   teamInfo struct visitingTeam

Returns:       Parameters passed-by-reference.
****************************************************************************/
void getInfoForTeams(teamInfo& homeTeam, teamInfo& visitingTeam) {

}

// Begin program execution here
int main()
{
teamInfo homeTeam, visitingTeam;
char  anotherGame, ch;

  do {
    getInfoForTeams(homeTeam, visitingTeam);
	predictGameOutcome(homeTeam, visitingTeam);

    cout << "\nDo you want to calculate for another game? (Y/N) ";
    cin >> anotherGame; 
	cin.get(ch);  // May need to "eat" the \n from the anotherGame input
  } while ((anotherGame == 'Y') || (anotherGame == 'y'));

  return(0);
}
