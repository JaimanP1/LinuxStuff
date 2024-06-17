#!/usr/bin/bash

function count_occurences(){
	word_to_search=$2
	file=$1

	output=`grep -o "$word_to_search" $file | wc -l`	
	echo "the word $word_to_search appears $output times in $file"
}

read -p "file to search " x
read -p "word to search " y

count_occurences $x $y
