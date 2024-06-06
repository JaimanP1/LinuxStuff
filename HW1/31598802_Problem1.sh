#!/usr/bin/bash

echo "Welcome to Rock, Paper, Scissors. You are playing the computer"

echo "Rock crushes Scissors, Scissors cuts Paper, Paper covers Rock. Use lowercase"

flag="true"

while [[ $flag == "true" ]]
do

	read -p "Enter your choice " choice

	#computer choice

	com_choice=$(($RANDOM % 3))

	#echo $com_choice
	if [ $com_choice -eq 0 ]
	then
		echo "Computer played Rock"
		if [ "$choice" == "rock" ]; then
			#$flag="tie"
			echo "Tie, try again"
		elif [ "$choice" == "paper" ]; then
			echo "You won"
			exit 0
		elif [ "$choice" == "scissors" ]; then
			echo "You lost"
			exit 0
		fi
	elif [ $com_choice -eq 1 ]
	then 
		echo "Computer played Paper"
		if [ "$choice" == "rock" ]; then
                	echo "You lost"
			exit 0
        	elif [ "$choice" == "paper" ]; then
                	#$flag="tie"
			echo "Tie, try again"
        	elif [ "$choice" == "scissors" ]; then
                	echo "You won"
			exit 0
        	fi
	elif [ $com_choice -eq 2 ]
	then 
		echo "Computer played Scissors"
		if [ "$choice" == "rock" ]; then
                	echo "You won"
			exit 0
        	elif [ "$choice" == "paper" ]; then
                	echo "You lost"
			exit 0
        	elif [ "$choice" == "scissors" ]; then
                	#$flag="tie"
			echo "Tie, try again"
        	fi
	fi
done	

