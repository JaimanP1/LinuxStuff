#!/usr/bin/bash

location=`pwd`
flag=""
while [[ $flag != "Quit"  ]];
do 
		
	read -p "Enter a directory name: " directory_name

	if [ ! -d "$directory_name" ]; then
		echo This directory does not exist. Would you like to make "$directory_name" at this location?
		read -p "Y/N: " user_input
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

	file_printer () {
		
		
		option="Yes"
		count=0
		lines=`cat $1 | wc -l`
		echo " "

		while [[ "$option" == "Yes" ]]; do
			if [ -f $1 ]; then
				#echo $count
				if [[ $count == 0 ]]; then
					echo `head $1`
				elif [[ $count -ge $lines ]]; then
					echo "The file only has $lines lines, no more to print. Exiting program."
					exit 0
				else
					echo `tail -n +$count --lines 10 $1`
				fi
			fi
			count=$((count + 10))
			read -p "To print the next ten lines, type 'Yes', else 'No' to quit: " option
		done

	}

	if [ -f $menu ]; then
		file_printer $menu
	elif [ -d $menu ]; then
		cd $menu
		echo "Select one of the following files: "
		current_date=$(date +%s)

		for file in *; do
		    if [ -f "$file" ]; then
			last_modified_time=$(date -r "$file" +%s)
			time_diff=$((current_date - last_modified_time))
			time_diff_hours=$((time_diff / 3600))
			if [ $time_diff_hours -lt 24 ]; then
			    echo "$file"
			fi
		    fi
		done 
		
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
		file_printer $menu
	else
		echo "logical error"
	fi
	cd $location
	echo $location
	read -p "If you would like to exit this program, type 'Quit', else this program will execute again (press 'Enter'): " flag
done



