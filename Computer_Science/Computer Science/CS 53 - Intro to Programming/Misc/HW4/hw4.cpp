//Matt Ludwikosky
//10/25/04
//Purpose: This program inputs 2 teams stats and predicts which team will win a game

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct teamInfo {
	string teamCity;
	string teamName;
	float strength;
	float chessRating;
	float purePoints;
	float powerRanking;
};

const int HOME_FIELD_ADVANTAGE_PTS = 3;

// Function declarations should go here...
string getTeamCity();
string getTeamName();
teamInfo getTeamInfo();
float calculatePowerRanking(const teamInfo team);
void predictGameOutcome(const teamInfo homeTeam, const teamInfo visitingTeam);
void getInfoForTeams(teamInfo& homeTeam, teamInfo& visitingTeam);

/****************************************************************************
Function name: getTeamCity

Description:   Read in a team's city. (Assume city may have spaces in it.)

Parameters:    None

Returns:       (string) city
****************************************************************************/
string getTeamCity() {
	string city;

	cout << "Enter team city:";
	cin >> city;

	return(city);
}

/****************************************************************************
Function name: getTeamName

Description:   Read in a team name. (Assume name has no spaces in it.)

Parameters:    None

Returns:       (string) name
****************************************************************************/
string getTeamName() {
	string name;

	cout << "Enter team name:";
	cin >> name;

	return(name);
}

/****************************************************************************
Function name: getTeamInfo

Description:   Get input for a team's information.

Parameters:    None

Returns:       teamInfo struct.
****************************************************************************/
teamInfo getTeamInfo() {
	teamInfo t;
	float temp;

	t.teamCity = getTeamCity();
	t.teamName = getTeamName();

	cout << "\nEnter strength of schedule rating:";
	cin >> temp;

	t.strength = temp;

	cout << "Enter ELO Chess rating:";
	cin >> temp;

	t.chessRating = temp;

	cout << "Enter Pure Points Predictor:";
	cin >> temp;

	t.purePoints = temp;

	t.powerRanking = calculatePowerRanking(t);

	return(t);
}

/****************************************************************************
Function name: calculatePowerRanking

Description:   Compute the given team's power ranking.

Parameters:    teamInfo struct team

Returns:       (float) power ranking.
****************************************************************************/
float calculatePowerRanking(const teamInfo team) {
	float powerRanking = ((team.strength + team.chessRating + team.purePoints)/3);

	return(powerRanking);
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
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);
	
	cout << "\nHOME team (" << homeTeam.teamCity << " " << homeTeam.teamName << ") has power ranking " << homeTeam.powerRanking;
	cout << "\nVISITING team (" << visitingTeam.teamCity << " " << visitingTeam.teamName << ") has power ranking " << visitingTeam.powerRanking << endl;

	cout.unsetf(ios::showpoint);
	cout.precision(0);

	if((homeTeam.powerRanking+3) > visitingTeam.powerRanking && ((homeTeam.powerRanking+3) - visitingTeam.powerRanking >= 1))
	{
		cout << homeTeam.teamCity << " " << homeTeam.teamName << " should beat "
			 << visitingTeam.teamCity << " " << visitingTeam.teamName << " by "
			 << (homeTeam.powerRanking+3) - visitingTeam.powerRanking << " point(s)";
	} else if((homeTeam.powerRanking+3) < visitingTeam.powerRanking && (visitingTeam.powerRanking - (homeTeam.powerRanking+3) >= 1))
	{
		cout << visitingTeam.teamCity << " " << visitingTeam.teamName << " should beat "
			 << homeTeam.teamCity << " " << homeTeam.teamName << " by "
			 << visitingTeam.powerRanking - (homeTeam.powerRanking+3) << " point(s)";
	} else
	{
		cout << homeTeam.teamCity << " " << homeTeam.teamName << " and the "
			 << visitingTeam.teamCity << " " << visitingTeam.teamName << " is too evenly matched to predict the outcome.";
	}

	return;
}

/****************************************************************************
Function name: getInfoForTeams

Description:   Prompt user to enter information for the 2 teams.

Parameters:    teamInfo struct homeTeam
			   teamInfo struct visitingTeam

Returns:       Parameters passed-by-reference.
****************************************************************************/
void getInfoForTeams(teamInfo& homeTeam, teamInfo& visitingTeam) {
	cout << "\nEnter information for the HOME team...\n\n";

	homeTeam = getTeamInfo();

	cout << "\nEnter information for the VISITING team...\n\n";

	visitingTeam = getTeamInfo();

	return;
}

// Begin program execution here
int main()
{
teamInfo homeTeam, visitingTeam;
char  anotherGame, ch;

  do {
    getInfoForTeams(homeTeam, visitingTeam);
	predictGameOutcome(homeTeam, visitingTeam);

    cout << "\n\nDo you want to calculate for another game? (Y/N) ";
    cin >> anotherGame; 
	cin.get(ch);  // May need to "eat" the \n from the anotherGame input
  } while ((anotherGame == 'Y') || (anotherGame == 'y'));

  return(0);
}
