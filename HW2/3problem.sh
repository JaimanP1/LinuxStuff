#!/bin/bash


#function to recursively traverse directories
#function to recursively traverse directories
recursive_traverse() {
        for obj in "$1"/*
        do
                if [ -f "$obj" ]; then
                        echo "$obj"
                else
                        echo "traversing directory: " "$obj"
                        recursive_traverse "$obj"
                fi
        done

}


current_path=$(pwd)

read -p "Enter a directory containing email addresses: " path

if [ ! -d "$path" ]; then
	echo "This is not a valid directory"
fi

#traversing directory for text files
recursive_traverse "$path"


#printing file with unique email addresses
cd $current_path

touch "unique_emails.txt"
