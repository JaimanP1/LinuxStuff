#!/bin/bash

if [ -f "$1" ]; then
	touch "${1}.bak"
else
	echo "file does not exist"
fi
