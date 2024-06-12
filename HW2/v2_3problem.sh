#!/bin/bash

read -p "Enter a directory: " path


# Function to recursively traverse directories
recursive_traverse() {
    for obj in "$1"/*
    do
        if [ -f "$obj" ]; then
           # echo "$obj"
            if [[ "$obj" == *.txt ]]; then
            #    echo "$obj is a text file"
                grep -E -o '[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}' "$obj" >> "$2"
            fi
        elif [ -d "$obj" ]; then
           # echo "traversing directory: $obj"
            recursive_traverse "$obj" "$2"
        fi
    done
}

output_file="unique_emails.txt"
temp_file="temp_emails.txt"
touch "$temp_file"
recursive_traverse "$path" "$temp_file"
sort "$temp_file" | uniq > "$output_file"
rm "$temp_file"

echo "Unique email addresses have been saved to $output_file"


