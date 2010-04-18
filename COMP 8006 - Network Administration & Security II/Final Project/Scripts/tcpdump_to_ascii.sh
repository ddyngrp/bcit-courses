#!/bin/bash
# Converts binary logs in all subdirectories to ASCII dumps

# First delete the old converted files
find ../data_indexing -name '*-index' -exec rm {} \;

# Convert all the binary files to text
find ../data_indexing -name 'snort.log.*[0-9]' -o -name 'tcpdump*' | while read line
do
	tcpdump -r "$line" -nn -XX -tt > "$line-index" &
done
