#!/bin/bash

read -p "Enter a directory: " path

#function to extract email addresses
extract() {
	grep -E '[[:alnum:]]*@[a-zA-Z]\.([a-zA-Z]){3}' $1 >> $2
}


#function to recursively traverse directories
recursive_traverse() {
	for obj in "$1"/*
        do
                if [ -f "$obj" ]; then
                        echo "$obj"
			if [[ "$obj" == *.txt ]]; then
				echo "$obj" is a text file
				extract "$obj" $2
			fi
                else
                        echo "traversing directory: " "$obj"
			recursive_traverse "$obj"
                fi
        done

}
touch "extracted_addresses.txt"
recursive_traverse $path "extracted_addresses.txt"
