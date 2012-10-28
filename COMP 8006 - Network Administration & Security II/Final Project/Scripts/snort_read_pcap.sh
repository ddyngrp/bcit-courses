#!/bin/bash
# Converts pcap files to the snort database

if [ "$1" == '' ]
then
	echo "Must provide a path..."
	exit 0
fi

# Import all snort.log files
find $1 -name 'snort.log.*' | while read line
do
	snort -c /etc/snort/snort.conf -r "$line"
done

# Import all tcpdump files
find $1 -name 'tcpdump*' | while read line
do
	snort -c /etc/snort/snort.conf -r "$line"
done
