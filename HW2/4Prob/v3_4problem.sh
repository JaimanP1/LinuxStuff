#!/bin/bash

read -p "Enter file containing personal information: " file

touch "temp_output.txt"
touch "temp2.txt"
touch "temp3.txt"

sed -n '/[[:alpha:]]\{1,\} [[:alpha:]]\{1,\}, [0-9]\{4\}-[0-9]\{2\}-[0-9]\{2\}, [[:alpha:]]\{1,\} [[:alpha:]]\{1,\}, [[:alpha:]]\{1,\}/p' "$file" > "temp_output.txt"

#cat "temp_output.txt"

sed -n 's/\([[:alpha:]]\{1,\} [[:alpha:]]\{1,\}\), \([0-9]\{4\}\).*/\2 \1/p' "temp_output.txt" > "temp2.txt"

while read line; do
    year=$(echo "$line" | sed 's/^\([0-9]\{4\}\).*/\1/')
    name=$(echo "$line" | sed 's/^[0-9]\{4\} \(.*\)/\1/')
    age=$((2024 - year))
    echo "$age $name" >> "temp3.txt"
done < "temp2.txt"

sort -n "temp3.txt"

rm "temp_output.txt"
rm "temp2.txt"
rm "temp3.txt"

