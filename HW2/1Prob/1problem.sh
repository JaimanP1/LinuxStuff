#!/bin/bash

# Count the words with at least three 'a's (case insensitive)
grep -oiw '\b\w*\w\w*\b' dictionary.txt | grep -i 'a' | tr '[:upper:]' '[:lower:]' | awk '{ count=0; for(i=1; i<=length($0); i++) if(substr($0,i,1)=="a") count++; if(count>=3) print $0 }' | wc -l


#grep -iE '.*ee.*' $1 | grep -ioE '.{3}$' | sort | uniq -c | sort -nr | head  > output3.txt

#grep -ioE '[a-zA-Z]{3}$' $1 | sort | uniq -c | sort -nr | head  > output4.txt

#grep -ioE '[a-zA-Z]{3}$' $1 | sort | uniq -c | sort -nr | head -n 1 > output4.txt

#grep -iE '[a-zA-Z]{3}$' $1 | sort > output4.txt

#tried [[:print:]]{3}$, only works for test file

#compare with v3, where is the difference in logic

#problem is occuring because it only works for the last word in the file, it is not delimited on words/newline characters properly
