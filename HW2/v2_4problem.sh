#!/bin/bash

read -p "Enter file containing personal information: " file

touch "temp_output.txt"
touch "temp2.txt"
touch "temp3.txt"

#going line by line over a file
sed -n '/[[:alpha:]]\{1,\} [[:alpha:]]\{1,\}, [0-9]\{4\}-[0-9]\{2\}-[0-9]\{2\}, [[:alpha:]]\{1,\} [[:alpha:]]\{1,\}, [[:alpha:]]\{1,\}/p' "$file" >> "temp_output.txt"

cat "temp_output.txt"

#filtering in form age, name
sed -n 's/\([[:alpha:]]\{1,\} [[:alpha:]]\{1,\},\) \([0-9]\{4\}\).*/\2\1/p' "temp_output.txt" >> "temp2.txt"

rm "temp_output.txt"
rm "temp3.txt"
