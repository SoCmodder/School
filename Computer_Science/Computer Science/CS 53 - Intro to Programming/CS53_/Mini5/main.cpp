/*
 * Author: Elliot Gross
 * Date: 4/6/06
 * Purpose:
 * Description: This program simulates a pinball game
 */
#include <iostream>
#include <fstream> // includes file i/o
#include "board.h"
#include "ball.h"

int main()
{
	Ball ball;//creates instance of Ball
	Board board; //creates instance of Board

	ifstream fin;//creates ifstream
	ofstream fout; //creates ofstream

	
	int m=0, n=0, cost=0, numBump=0;
	int x =0,y =0, points = 0, Wallcost=0;
	int numPoints = 0, numLife = 0;
	DIRECTION currentDir = RIGHT;
	int ballX=0, ballY=0, direction=0, life=0; //variable declarations
	
	
	
	
	fin.open("input.dat");//opens file
	if (fin.fail())//error checking
	{
		cout << "ERROR: Input file opening failed" << endl;
	}
	
	fout.open("output.dat");//opens output file
	if (fout.fail())//error checking
	{
		cout << "ERROR: Output file opening failed" <<endl;
	}
		
	 
	fout << "Name of File: " << "ouput.dat"<< endl;//sends to output file
	

		fin >> m; //gets in length
	    fin >> n; //gets in width
		board.setLength(m);//calls setLength
		board.setWidth(n);//calls setWidth
		board.mkWall(m,n);//calls mkWall
		fin >> Wallcost; //gets Wallcost
		fin >> numBump; //gets numBump
		for (int i=0; i <= numBump; i++)//makes bumper based on numBump
		{
			fin >> x; //gets x coord of bumper
			fin >> y; // gets y coord of bumper
			fin >> points; //gets bumper points
			fin >> cost; //gets bumper cost
			board.mkBumper(x, y, points, cost);//calls mkBumper
		}
	do
	{
		
		fin >> ballX;//gets initial X coord of ball
		fin >> ballY;// gets initial Y coord of ball 
		fin >> direction; //gets initial direction
		if (direction == 0)
			ball.setDirection(RIGHT);
		if (direction == 1)
			ball.setDirection(UP);
		if (direction == 2)
			ball.setDirection(LEFT);
		if (direction == 3)
			ball.setDirection(DOWN);
		fin >> life; //gets initial life
	
		numLife = ball.getLife(); //sets current life
		currentDir = ball.getDirection();//sets current direction
		
		do
		{
				board.move(currentDir, ballX, ballY, numLife, Wallcost, numPoints);
				//moves the ball
				ball.setPoints(numPoints);//sets points
				ball.setLife(numLife);//sets life
				ball.setDirection(currentDir);//sets direction
		
			
		}while(ball.getLife() > 0);
		fout << ball.getPoints() << endl;//sends output to output file
		numPoints = 0;//resets numPoints
	}while(!fin.eof());	//goes until end of file

	float next, sum = 0;
	while(fin >> next)
		sum = sum + next;//gets the sum
   	fout << sum << endl;//sends sum to output file

	fin.close();//closes stream
	fout.close();//closes stream



	return 0;

}
