#!/bin/bash
#REMEBER TO TYPE IN NUMBER OF ELEMENTS
count=$1
rm -f input
rm -f your_output
rm -f standard_output
echo "================== input ======================"
echo ${count} | tee input
for (( i=0; i<${count}; i++ )); do
    echo $RANDOM done | tee -a input
done
echo "============= execution result ================"
cat input | ./v2 | tee your_output
tail -n +2 input | sort -n > standard_output
echo "====== differences from correct result ======="
diff your_output standard_output

