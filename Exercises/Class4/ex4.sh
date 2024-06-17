#!/bin/bash

if [ ! -d "$1" ]
then
	echo "directory does not exist"
	exit 12
fi

files=("$1"/*)

for i in "{files[@]}"
do
	n=`echo $i | tr a-z A-Z`
	if [ "$i" != $n ]
	then
		mv "$i" "$n"
	exit 0
	fi
done
