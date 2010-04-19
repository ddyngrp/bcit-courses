#!/bin/bash
# Converts binary logs in all subdirectories to ASCII dumps

if [ "$1" == '' ]
then
	echo 'Must provide a path...'
	exit 0
fi

# Convert all the binary files to text
find $1 -name 'snort.log.*[0-9]' -o -name 'tcpdump*' | while read line
do
	tcpdump -r "$line" -nn -X -tt 'ip' > "$line-index" && rm "$line" && mv "$line-index" "$line" &
done
