#!/bin/bash
# Converts binary tcpdump logs in all subdirectories to ASCII dumps

# First delete the old converted files
find ../ -name tcpdump*.txt -exec rm -rf {} \;

# Convert all the binary files to text
find ../ -name tcpdump* | while read line
do
	tcpdump -r "$line" -tt > "$line.txt" &
done
