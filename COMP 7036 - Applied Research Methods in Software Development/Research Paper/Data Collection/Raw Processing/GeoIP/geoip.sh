#!/bin/bash

# Read file
exec< $1

while read line
do
	curl "http://api.hostip.info/get_html.php?ip=$line&position=true" >> hostip.txt
	echo -n "|" >> hostip.txt
done
