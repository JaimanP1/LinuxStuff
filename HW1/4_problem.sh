#!/usr/bin/bash

read -p "Enter a directory name " directory_name

if [ ! -d "$directory_name" ]; then
	echo This directory does not exist. Would you like to make "$directory_name" at this location?
	read -p "Y/N " user_input
	if [[ $user_input == "Y" ]]; then
		mkdir "$directory_name"
	else
		exit 0
	fi
fi

cd "$directory_name"

echo `pwd`
echo Directory contents:
echo " "
echo `ls`
echo " "

while_condition="false"
menu=" "

while [[ $while_condition == "false" ]]; do
	read -p "Type the name of the file/directory you would like to select, press 'Q' to quit: " menu

	if [[ $menu == "Q" ]]; then
		echo Exiting program
		exit 0

	elif [ ! -e "$menu" ]; then
        	echo "This file/directory does not exist"
	else
		while_condition="true"
	fi
done

option="Yes"
count=0
while [[ "$option" == "Yes" ]]; do
	if [ -e $menu ]; then
		echo $count
        	echo `tail -n + $count`
	fi
	count=$((count + 10))
	read -p "To print the next ten lines, type 'Yes': " option
done

#need to find a way to update lines of file to be read. otherwise will just keep printing first 10 lines
#head -n4 example.lst | tail -n+2
