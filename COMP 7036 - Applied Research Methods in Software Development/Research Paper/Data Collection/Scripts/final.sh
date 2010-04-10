# Traceroute data collection Script
#!/bin/sh

ROUTE_SERVERS="203.202.125.6
			   216.113.10.50
			   213.192.191.82
			   62.48.45.129
			   196.25.9.46
			   69.31.111.255
			   154.11.98.18
			   216.191.14.250
			   216.18.63.214
			   213.200.64.94
			   86.55.0.50
			   164.128.251.50
			   212.241.174.1
			   66.162.47.58
			   64.135.5.58
			   12.129.193.235
			   66.209.87.106"
NOW=$(date +"%Y-%m-%d")
COLLECTOR="steffen-final"

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
