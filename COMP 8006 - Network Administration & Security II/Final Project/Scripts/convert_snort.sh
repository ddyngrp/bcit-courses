#!/bin/bash
# Converts binary snort logs in all subdirectories to ASCII dumps

# First delete the old converted files
find ../ -name snort.log.*.txt -exec rm -rf {} \;

# Convert all the binary files to text
find ../ -name snort.log.*[0-9] | while read line
do
	tcpdump -r "$line" -tt > "$line.txt" &
done
