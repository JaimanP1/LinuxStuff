#!/bin/bash

read -p "enter filename: " file

if [ -z $file ]
then 
	echo "No filename provided"
	exit 1
fi

if [ -f $file ] 
then
	tail $file
else
	echo "$file does not exist"
fi
