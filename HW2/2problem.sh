#!/bin/bash

if [[ $# != 1 ]]; then
	echo "Need an input file"
fi

if [ -f "./scanf_log.txt" ]; then
	echo "File exists"
else
	echo "Making file scanf_log.txt in this directory"
	touch "./scanf_log.txt"
fi

if [ -f "./printf_log.txt" ]; then
	echo "file exists"
else 
	echo "Making file printf_log.txt in this directory"
	touch "./printf_log.txt"
fi

total_lines=`cat $1 | wc -l`

echo Total lines: $total_lines

printf_freq=`grep 'printf' $1 | wc -l`
scanf_freq=`grep 'printf' $1 | wc -l`

echo Number of lines containing printf: $printf_freq
echo Number of lines containing scanf: $scanf_freq

echo "Percentage 'printf' (to nearest whole percent): " $(( $printf_freq * 100 / $total_lines ))%

echo "Percentage 'scanf' (to nearest whole percent): " $(( $scanf_freq * 100 / $total_lines ))%

grep 'printf' $1 >> printf_log.txt

grep 'scanf' $1 >> scanf_log.txt


