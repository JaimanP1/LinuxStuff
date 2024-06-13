#!/bin/bash

if [[ $# -lt 1 ]]; then
  echo "Too few arguments"
  exit 0
fi

grep -oE '\b\w*ee\w*\b' "$1" | grep -oE '.{3}$' | sort | uniq -c | sort -nr | head -n 1 > output3.txt


