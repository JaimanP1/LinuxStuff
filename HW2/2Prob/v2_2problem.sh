#!/bin/bash

total_lines=`cat $1 | wc -l`

echo $total_lines

printf_freq=`grep 'printf' $1 | wc -l`
scanf_freq=`grep 'printf' $1 | wc -l`

echo $printf_freq
echo $scanf_freq

echo "Percentage 'printf' (to nearest whole percent): " $(( $printf_freq * 100 / $total_lines ))%

echo "Percentage 'scanf' (to nearest whole percent): " $(( $scanf_freq * 100 / $total_lines ))%


