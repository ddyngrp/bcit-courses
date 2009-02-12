#!/bin/bash

# This creates a file that is slightly larger than our message
# buffer. This is to test the messages are fully sent.
rm ./numbers
echo "--begin--" >> ./numbers
for i in $(seq 0 410)
do
	for k in $(seq 0 9)
	do
		printf $k >> ./numbers
	done
done
echo >> ./numbers
echo "--end--" >> ./numbers

# This creates a 200,000 line file for simple throughput testing.
rm ./sequence
for i in $(seq 0 200000)
do
	echo $i >> ./sequence
done
