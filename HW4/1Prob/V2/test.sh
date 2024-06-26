#!/bin/bash

# Ensure the count argument is provided
if [ -z "$1" ]; then
    echo "Usage: $0 <count>"
    exit 1
fi

count=$1

# Check if count is a non-negative integer
if ! [[ "$count" =~ ^[0-9]+$ ]]; then
    echo "Error: count must be a non-negative integer"
    exit 1
fi

rm -f input
rm -f your_output
rm -f standard_output

echo "================== input ======================"
echo ${count} | tee input
for (( i=0; i<${count}; i++ )); do
    echo $RANDOM | tee -a input
done

echo "============= execution result ================"
cat input | ./v2 | tee your_output

tail -n +2 input | sort -n > standard_output

echo "====== differences from correct result ======="
diff your_output standard_output

