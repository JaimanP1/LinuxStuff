#!/bin/bash

read -p "Enter file containing personal information: " file

touch "temp_output.txt"

#going line by line over a file
sed -n '/[[:alpha:]]\{1,\} [[:alpha:]]\{1,\}, [0-9]\{4\}-[0-9]\{2\}-[0-9]\{2\}, [[:alpha:]]\{1,\} [[:alpha:]]\{1,\}, [[:alpha:]]\{1,\}/p' "$file" >> "temp_output.txt"

cat "temp_output.txt"
sed -n 's/.*\([0-9]\{4\}\).*/\1/p' "temp_output.txt"

rm "temp_output.txt"
