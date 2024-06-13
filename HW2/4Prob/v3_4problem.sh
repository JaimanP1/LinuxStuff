#!/bin/bash

read -p "Enter file containing personal information: " file

touch "temp_output.txt"
touch "temp2.txt"
touch "temp3.txt"

# Extract lines matching the pattern and save them to temp_output.txt
sed -n '/[[:alpha:]]\{1,\} [[:alpha:]]\{1,\}, [0-9]\{4\}-[0-9]\{2\}-[0-9]\{2\}, [[:alpha:]]\{1,\} [[:alpha:]]\{1,\}, [[:alpha:]]\{1,\}/p' "$file" > "temp_output.txt"

# Display the contents of temp_output.txt
cat "temp_output.txt"

# Extract the year and name, and save them to temp2.txt
sed -n 's/\([[:alpha:]]\{1,\} [[:alpha:]]\{1,\}\), \([0-9]\{4\}\).*/\2 \1/p' "temp_output.txt" > "temp2.txt"

# Calculate the age for each entry and save it to temp3.txt
while IFS= read -r line; do
    year=$(echo "$line" | sed 's/^\([0-9]\{4\}\).*/\1/')
    name=$(echo "$line" | sed 's/^[0-9]\{4\} \(.*\)/\1/')
    current_year=$(date +%Y)
    age=$((current_year - year))
    echo "$age $name" >> "temp3.txt"
done < "temp2.txt"

# Sort the results by age and display them
sort -n "temp3.txt"

# Clean up temporary files
rm "temp_output.txt"
rm "temp2.txt"
rm "temp3.txt"

