###
###Programmer: Mitch Miller
###Class: Introduction to Operating Systems
###Assignment: Assignment 1
###
###
###
#!/bin/sh

printMenu()
{
    echo "1. Print the ancestry tree of the currently running process.";
    echo "2. Print users that are online currently.";
    echo "3. View the processes of a certain user.";
    echo "4. Exit.";
}

ancestryTree()
{
	### I need to store this in a file
	### from there we can read the number and move up the list
	###TODO: DERP
	getId()
	{
	ps -p $$ -o ppid=;
	}
}

input=0
echo "Welcome User, Please make a selection from the following menu:"
while [ input!=4 ]
do
    printMenu
    read input
    case $input in
    1) ancestryTree;;
    2) echo "You chose 2";;
    3) echo "You chose 3";;
    4) echo "You chose 4";;
    *) echo "Please choose one of the options listed in the menu.";;
    esac
done
