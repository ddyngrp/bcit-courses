#!/usr/local/bin/bash
#
# This script simply runs doxygen to generate the html documentation and prints
# any errors or warnings at the end of the output, reducing the amount of
# scrolling through the warnings.

# File to redirect doxygen's stderr to
DOXYLOG=doxygen.errors

# Run doxygen and redirect stderr to file
doxygen Doxyfile 2>$DOXYLOG

# Display file content if the file is not empty
if [ -s $DOXYLOG ]; then
	echo -e "\033[31mErrors/warnings:\033[0m"
	cat $DOXYLOG
else
	echo -e "\033[32mOK - no errors or warnings\033[0m"
fi
