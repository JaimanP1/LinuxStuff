#!/bin/bash

read -p "Enter a directory: " path

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

recursive_traverse $path 
