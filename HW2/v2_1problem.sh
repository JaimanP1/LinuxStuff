#!/bin/bash

echo "The number of words with at least 3 'a':" `grep -i '.*[a].*[a].*[a].*' $1 | wc -l`

grep -i '.*[a].*[a].*[a].*' $1 > output1.txt

echo "The number of words with 3 'e' non-consecutively:" `grep -iE '((([^Ee])e){3})|E([^e]+e){2}' $1 | wc -l`

grep -iE '((([^Ee])e){3})|E([^e]+e){2}' $1 > output2.txt

#Matches 4 'e' expressions, need to fix
