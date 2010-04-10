# Traceroute data collection Script
#!/bin/sh

ROUTE_SERVERS="154.11.98.18
			   216.191.14.250
			   216.18.63.214
			   213.200.64.94
			   86.55.0.50"
NOW=$(date +"%Y-%m-%d")
COLLECTOR="clayton"

LOG_FILE="./$(date +"%Y-%m-%d.%H.%M.%S")-${COLLECTOR}"

for server in $ROUTE_SERVERS
do
	echo "Connecting to $server..."
	telnet $server 2>&1 | tee -a $LOG_FILE.log
	echo
	read -p "*** Press ENTER to continue ***"
	echo

done

echo "Finished colleting data for $NOW..."
