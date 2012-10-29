#!/bin/bash
# Open the port to allow inbound packets
iptables -i eth0 -A INPUT -s $1 -p tcp --dport $2 -j ACCEPT
sleep 10
#Delete the rule after 10 seconds
iptables -i eth0 -D INPUT -s $1 -p tcp --dport $2 -j ACCEPT
