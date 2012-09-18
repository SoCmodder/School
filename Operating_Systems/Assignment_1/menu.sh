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
	myData=($(ps -p $$ -o ppid=))
	
	while [ "$myData" != 1 ]
	do
		echo "    "$myData
		echo "      |      "
		stat=($(</proc/$myData/stat))
		ppid=(${stat[3]})
		echo "    "$ppid
		echo "      |"
		myData=$ppid
	done
}

usersOnline()
{
	who | awk '{print $1}' | sort -u
}

processOfUser()
{
	i=0
	arr[0]=
	while read value; do
		arr["$i"]="$value"
		echo $i". " ${arr[$i]}
		i=i+1
	done < <(who | awk '{print $1}' | sort -u)
	
	echo "Please Select a user from a list to view their processes."
	read input
	case $input in
	
}

input=0
echo "Welcome User, Please make a selection from the following menu:"
while [ input!=4 ]
do
    printMenu
    read input
    case $input in
    1) ancestryTree;;
    2) usersOnline;;
    3) processOfUser;;
    4) break;;
    *) echo "Please choose one of the options listed in the menu.";;
    esac
done
