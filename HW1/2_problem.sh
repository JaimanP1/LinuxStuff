#!/usr/bin/bash

name="$1"

if [ $# -lt 1 ]; then
	read -p "Enter a name of a file or directory " name

fi

if [ ! -e $name ]; then
	echo "No such file or directory"
	exit 1
elif [ -f $name ]; then
	echo "File exists"
	permissions=$(stat -c %A $name | cut -c2-4)
	first_char=${permissions:0:1}
	last_char=${permissions: -1}
	if [ ! $first_char = r ] || [ ! $last_char = x ]; then
		echo "You do not have read and/or execute permission"
	elif [ $first_char = r ]; then	
		words=$(wc -w < $name)
		lines=$(wc -l < $name)
		characters=$(wc -c < $name)
		echo "The number of words are $words"
		echo "The number of lines are $lines"
		echo "The number of characters are $characters"
		if [ $characters -gt 10000 ]; then
			echo "Text Heavy"
		elif [ $characters -lt 1000 ]; then
			echo "Light File"
		else
			echo "Moderately Sized"
		fi
	fi
elif [ -d $name ]; then
	echo "Directory exists"
       	permissions=$(stat -c %A $name | cut -c2-4)
        first_char=${permissions:0:1}
        last_char=${permissions: -1}
        if [ ! $first_char = r ] || [ ! $last_char = x ]; then
                echo "You do not have read and/or execute permission"
	else
		echo `ls | wc -l`
		echo `du -ah $name`
	fi
else
	echo "Weird case"
fi


