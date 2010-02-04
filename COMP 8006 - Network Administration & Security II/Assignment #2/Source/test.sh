###############################################################################
#
#!/bin/bash
#
# SOURCE FILE: internal-test.sh
# 
# PROGRAM:     Firewall testing script from inside the network.
# 
# DATE:        February 3, 2010
# 
# REVISIONS:   
# 
# DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
# 
# PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
# 
###############################################################################


###############################################################################
# 
# User Configurable Section
#
###############################################################################

# Output File
OUTPUT="./internal-test"

# Allowed TCP Ports
TCP_ALLOWED="20 21 22 53 80"

# Allowed ICMP types
ICMP_ALLOWED="8 11"

# Always Blocked
TCP_BLOCKED="32768 32769 32770 32771 32772 32773 32774 32775 137 138 139 111 515"

# Server
SERVER="trollop.org"


###############################################################################
# 
# Implementation Section
#
###############################################################################

rm $OUTPUT

# hping3 the server and port using a SYN
testTCP() {
	hping3 $1 -c 1 --tcpexitcode -p $2 -S &>> $OUTPUT
	echo $?
}

printOutput() {
	case $1 in
		18)	
			echo "Port $port is open and service is running on $SERVER."
			echo >> $OUTPUT
			echo "** Port $port is open and service is running on $SERVER." >> $OUTPUT
			echo >> $OUTPUT
			;;
		20)	
			echo "Port $port is open, but no service is responding on $SERVER."
			echo >> $OUTPUT
			echo "** Port $port is open, but no service is responding on $SERVER." >> $OUTPUT
			echo >> $OUTPUT
			;;
		1)	
			echo "Port $port is closed on $SERVER."
			echo >> $OUTPUT
			echo "** Port $port is closed on $SERVER." >> $OUTPUT
			echo >> $OUTPUT
			;;
		*)	
			echo "Requests to port $port are DROPPED."
			echo >> $OUTPUT
			echo "** Requests to port $port are DROPPED." >> $OUTPUT
			echo >> $OUTPUT
			;;
	esac
}

echo "Testing allowed TCP ports $TCP_ALLOWED on $SERVER"
echo "################################################################" >> $OUTPUT
echo "# Testing allowed TCP ports $TCP_ALLOWED on $SERVER" >> $OUTPUT
echo "################################################################" >> $OUTPUT
for port in $TCP_ALLOWED
do
	printOutput `testTCP $SERVER $port`
done

echo "Testing blocked TCP ports $TCP_BLOCKED on $SERVER"
echo "################################################################" >> $OUTPUT
echo "# Testing blocked TCP ports $TCP_BLOCKED on $SERVER" >> $OUTPUT
echo "################################################################" >> $OUTPUT
for port in $TCP_BLOCKED
do
	printOutput `testTCP $SERVER $port`
done
