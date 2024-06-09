#!/bin/bash

# Ensure the script takes at least one argument
if [[ $# -lt 1 ]]; then
  echo "Too few arguments"
  exit 0
fi

# Find words with at least two adjacent 'e's, then extract the last 3 characters of each word,
# sort, count, and find the most common sequence
grep -oE '\b\w*ee\w*\b' "$1" | grep -oE '.{3}$' | sort | uniq -c | sort -nr | head -n 1 > output3.txt


