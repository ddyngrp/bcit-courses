# Traceroute data collection Script
#!/bin/sh

ROUTE_SERVERS="164.128.251.50
			   212.241.174.1
			   66.162.47.58
			   64.135.5.58
			   12.129.193.235"
NOW=$(date +"%Y-%m-%d")
COLLECTOR="brendan"

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
