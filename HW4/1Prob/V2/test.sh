#!/bin/bash
count=$1
rm input
rm your_output
rm standard_output
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

