#!/bin/bash

if [ $# -ne 1 ]; then
	echo 1>&2 Usage: $0 [program location]
	exit 127
fi

ls -lL `ldd $1 | cut -d \  -f 3 | grep "/"`
