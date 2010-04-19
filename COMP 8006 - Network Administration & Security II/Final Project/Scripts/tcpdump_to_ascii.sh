#!/bin/bash
# Converts binary logs in all subdirectories to ASCII dumps

# Convert all the binary files to text
find ../data_indexing -name 'snort.log.*[0-9]' -o -name 'tcpdump*' | while read line
do
	tcpdump -r "$line" -nn -X -tt 'ip' > "$line-index" && rm "$line" && mv "$line-index" "$line" &
done
