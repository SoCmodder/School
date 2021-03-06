###
###	Programmer: Mitch Miller
###	Class: Operating Systems
###	Assignment: Assignment 1
###
###
#!/bin/sh

printMenu()
{
	echo 1. "Print the ancestry tree of the currently running process.";
	echo 2. "Print users that are online";
	echo 3. "View the processes of a certain user.";
	echo 4. "Exit";
}
input=0
echo "Welcome User, Please make a selection:"
while [ input!=4 ]
do
	printMenu
	read input
	case $input in
		1) echo "You chose 1";;
		2) echo "You chose 2";;
		3) echo "You chose 3";;
		4) echo break;;
		*) echo "Please choose one of the options listed in the menu.";;
	esac
done
