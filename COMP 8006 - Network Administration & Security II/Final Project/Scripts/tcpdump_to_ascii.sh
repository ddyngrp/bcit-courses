#!/bin/bash
# Converts binary logs in all subdirectories to ASCII dumps

# First delete the old converted files
find ../data_indexing -name snort.log.*.txt -exec rm -rf {} \;

# Convert all the binary files to text
find ../data_indexing -name snort.log.*[0-9] | while read line
do
	tcpdump -r "$line" -tt > "$line.txt" &
done

# First delete the old converted files
find ../data -name tcpdump*.txt -exec rm -rf {} \;

# Convert all the binary files to text
find ../data -name tcpdump* | while read line
do
	tcpdump -r "$line" -tt > "$line.txt" &
done
