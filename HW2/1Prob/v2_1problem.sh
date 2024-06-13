#!/bin/bash

if [[ $# -lt 1 ]]; then 
	echo "Too few arguments"
	exit 0
fi

echo "The number of words with at least 3 'a':" `grep -i '.*[a].*[a].*[a].*' $1 | wc -l`

#grep -i '.*[a].*[a].*[a].*' $1 > output1.txt

echo "The number of words with 3 'e' non-consecutively:" `grep -iE '((([^Ee])e){3})|E([^e]+e){2}' $1 | wc -l`

#grep -iE '((([^Ee])e){3})|E([^e]+e){2}' $1 > output2.txt

#Matches 4 'e' expressions, need to fix

echo "The most common last three characters for words with consecutive e: " `grep -oE '\b\w*ee\w*\b' "$1" | grep -oE '.{3}$' | sort | uniq -c | sort -nr | head -n 1`

#grep -oE '\b\w*ee\w*\b' "$1" | grep -oE '.{3}$' | sort | uniq -c | sort -nr | head -n 1 > output3.txt

