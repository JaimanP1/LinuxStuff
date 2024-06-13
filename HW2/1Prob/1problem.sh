#!/bin/bash

# Count the words with at least three 'a's (case insensitive)
grep -oiw '\b\w*\w\w*\b' dictionary.txt | grep -i 'a' | tr '[:upper:]' '[:lower:]' | awk '{ count=0; for(i=1; i<=length($0); i++) if(substr($0,i,1)=="a") count++; if(count>=3) print $0 }' | wc -l

