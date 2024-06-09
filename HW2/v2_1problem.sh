#!/bin/bash

if [[ $# -lt 1 ]]; then 
	echo "Too few arguments"
	exit 0
fi

echo "The number of words with at least 3 'a':" `grep -i '.*[a].*[a].*[a].*' $1 | wc -l`

grep -i '.*[a].*[a].*[a].*' $1 > output1.txt

echo "The number of words with 3 'e' non-consecutively:" `grep -iE '((([^Ee])e){3})|E([^e]+e){2}' $1 | wc -l`

grep -iE '((([^Ee])e){3})|E([^e]+e){2}' $1 > output2.txt

#Matches 4 'e' expressions, need to fix

echo "The words with two consecutive 'e' with three characters at the end: "

grep -iE '.*ee.*' $1 | grep -ioE '.{3}$' | sort | uniq -c | sort -nr | head  > output3.txt

#grep -ioE '[a-zA-Z]{3}$' $1 | sort | uniq -c | sort -nr | head  > output4.txt

grep -ioE '[a-zA-Z]{3}$' $1 | sort | uniq -c | sort -nr | head -n 1 > output4.txt

grep -iE '[a-zA-Z]{3}$' $1 | sort > output4.txt

#tried [[:print:]]{3}$, only works for test file 

#compare with v3, where is the difference in logic 

#problem is occuring because it only works for the last word in the file, it is not delimited on words/newline characters properly
