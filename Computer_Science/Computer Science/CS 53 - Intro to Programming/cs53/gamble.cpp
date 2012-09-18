#include <iostream>
#include <ctime>
#include <cstdlib>//need to have this for random function
using namespace std;

int rolldie();//function for gettin a random dice roll
int gamestatus1(int totalroll);//function for determining status of initial roll
void points(int pointset);//function for rolling if you go to points
int diceone;//variable to be assigned to one of the dice
int dicetwo;//variable to be assigned to another of the dice
int totalroll;//the total roll between the two dice
int status;//a status value for the game
int pointset;//is the total roll number from first roll that is transfered to points
char userinput;//input for user to chose to cont. or not

int main()//main function

{
do//inside of loop is executed while user wants to keep playing
 {
    srand(time(0));// seeds random function
    diceone=rolldie();//gets a random value for first die
    dicetwo=rolldie();//gets a random value for second die
    totalroll = diceone + dicetwo;//the total value of the roll
    cout<<"Player rolled "<<diceone<<" + "<<dicetwo<<" = "<<totalroll<<endl;
    status=gamestatus1(totalroll);//calls the function to determine game status
    if(status==1)
    cout<<"Player Wins!"<<endl;//status says player wins
    if(status==2)
    cout<<"Player loses."<<endl;//status says player loses
    if(status==3)//status says we need to go to points
     {
     pointset = totalroll;
     points(pointset); //takes the value of totalroll and goes to points
     }
     cout<<"Do you want to play again? (Y/N)"<<endl;//lets user chose weither they want to cont or not
     cin>>userinput;
  }while(userinput=='y'||userinput=='Y'); 
return 0;
}
/**********************************************
Function rolldie creats a random number that is used as a one of the dice it reurns
a value from 1-6 to main 
**********************************/
int rolldie()
{
  int die;
  die = 1 + rand()%6;
  return die;
}
/**********************************************
Function gamestatus1 is a function that takes the value of the first rool and assigns a value
to a variable based on the status of weither or not the player has won lost or is going to 
go to points. This one of three values is returned to main and main choses where to go from
that value.
*****************************************/
int gamestatus1(int totalroll)
{
   int temp;
   if (totalroll==7 || totalroll==11)  
   temp=1;
   if (totalroll==2||totalroll==3||totalroll==12)
   temp=2;
   if (totalroll==4||totalroll==5||totalroll==6||totalroll==8||totalroll==9||totalroll==10)
   temp=3;
   return temp;
}

/*************************************************
Function points is the function that is called if the users first roll tells him to go to
points this function only has what the total roll fomr the first roll passed to it. The 
function continues rolling the dice until it gets a total roll of either the points total
or the number 7. If the player matches the points value then they win and if they
match 7 before they reach the point they lose. It displays the outcome and then returns the
user to the main function.
************************************************/
void points(int pointset)
{
  int die1;
  int die2;
  int rollsum;
  cout<<"Point is "<<pointset<<endl;
  do
    {
     die1=rolldie();
     die2=rolldie();
     rollsum=die1+die2;
     cout<<"Player rolled "<<die1<<" + "<<die2<<" = "<<rollsum<<endl;
    }while((pointset!=rollsum)&&(rollsum!=7));
    if (pointset==rollsum)
    {
    cout<<"Player Wins!"<<endl;
    }
    else
    {
    cout<<"Plater Loses"<<endl;
    }
    return;
} 
