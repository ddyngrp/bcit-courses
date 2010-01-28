###############################################################################
#
#!/bin/bash
#
# SOURCE FILE: firewall.sh
# 
# PROGRAM:     Simple personal firewall.
# 
# DATE:        January 27, 2010
# 
# REVISIONS:   
# 
# DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
# 
# PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
# 
# NOTES: This script uses iptables to perform the following rules:
#        - Default policy set to DROP
#        - ALLOW inbound/outbound SSH packets
#        - ALLOW inbound/outbound WWW packets
#        - ALLOW outbound DNS traffic
#        - ALLOW outbound DHCP traffic
#        - DROP all inbound traffic to port 80 from source port < 1024
#        - DROP all inbound traffic to reserved port 0
#        - DROP all inbound traffic from reserved port 0
#        - DROP all bad packets (SYN coming the wrong way, etc...)
#
#        Enable the following accounting rules:
#        - WWW and SSH traffic
#
###############################################################################
 

###############################################################################
# 
# Local Settings
#

# Set PATH
IPT="/sbin/iptables"
IPTS="/sbin/iptables-save"
IPTR="/sbin/iptables-restore"
SYSCTL="/sbin/sysctl -w" 

# Outside interface
LOCAL_IFACE="eth0"

# Localhost interface
LO_IFACE="lo"
LO_IP="127.0.0.1"

# Save and restore arguments handled here
if [ "$1" = "save" ]
then
	echo -n "Saving firewall to `pwd`/iptables-save ... "
	$IPTS > ./iptables-save
	echo "done"
	exit 0
elif [ "$1" = "restore" ]
then
	echo -n "Restoring firewall from `pwd`/iptables-save ... "
	$IPTR < ./iptables-save
	echo "done"
	exit 0
fi

###############################################################################
#
# Load Modules
#
echo "Loading kernel modules ..."

# Core netfilter module
/sbin/modprobe ip_tables

# Stateful connection tracking module
/sbin/modprobe ip_conntrack


###############################################################################
#
# Kernel Parameter Configuration
#

# This enables SYN flood protection.
if [ "$SYSCTL" = "" ]
then
    echo "1" > /proc/sys/net/ipv4/tcp_syncookies
else
    $SYSCTL net.ipv4.tcp_syncookies="1"
fi


###############################################################################
#
# Flush Any Existing Rules or Chains
#

cleanOldRules() {
	echo "Flushing Tables ..."

	# Reset Default Policies
	$IPT -P INPUT ACCEPT
	$IPT -P FORWARD ACCEPT
	$IPT -P OUTPUT ACCEPT
	$IPT -t nat -P PREROUTING ACCEPT
	$IPT -t nat -P POSTROUTING ACCEPT
	$IPT -t nat -P OUTPUT ACCEPT
	$IPT -t mangle -P PREROUTING ACCEPT
	$IPT -t mangle -P OUTPUT ACCEPT

	# Flush all rules
	$IPT -F
	$IPT -t nat -F
	$IPT -t mangle -F

	# Erase all non-default chains
	$IPT -X
	$IPT -t nat -X
	$IPT -t mangle -X
}

cleanOldRules

# Clear all rules
if [ "$1" = "stop" ]
then
	echo "Firewall completely flushed!  Now running with no firewall."
	exit 0
fi


###############################################################################
#
# Rules Configuration
#

### Set default policies ###

echo "Setting default policy to DROP ..."
$IPT -P INPUT DROP
$IPT -P OUTPUT DROP
$IPT -P FORWARD DROP

# User-defined chains
echo "Create and populate custom rule chains ..."

# Create a chain to filter INVALID packets
$IPT -N bad_packets
$IPT -N bad_tcp_packets

# Inbound/outbound UDP packets
$IPT -N udp_inbound
$IPT -N udp_outbound

# Inbound/outbound TCP packets
$IPT -N tcp_inbound
$IPT -N tcp_outbound


### Populate user-defined chains ###

# Drop INVALID packets immediately
$IPT -A bad_packets -p ALL -m state --state INVALID -j LOG --log-prefix "Invalid packet: "
$IPT -A bad_packets -p ALL -m state --state INVALID -j DROP

# Then check the tcp packets for additional problems
# return if ok.
$IPT -A bad_packets -p tcp -j bad_tcp_packets
$IPT -A bad_packets -p ALL -j RETURN

# bad_tcp_packets chain
$IPT -A bad_tcp_packets -p tcp -i $LOCAL_IFACE -j RETURN
$IPT -A bad_tcp_packets -p tcp ! --syn -m state --state NEW -j LOG --log-prefix "New not syn: "
$IPT -A bad_tcp_packets -p tcp ! --syn -m state --state NEW -j DROP
$IPT -A bad_tcp_packets -p tcp --tcp-flags ALL NONE -j LOG --log-prefix "Stealth scan: "
$IPT -A bad_tcp_packets -p tcp --tcp-flags ALL NONE -j DROP
$IPT -A bad_tcp_packets -p tcp --tcp-flags ALL ALL -j LOG --log-prefix "Stealth scan: "
$IPT -A bad_tcp_packets -p tcp --tcp-flags ALL ALL -j DROP
$IPT -A bad_tcp_packets -p tcp --tcp-flags ALL FIN,URG,PSH -j LOG --log-prefix "Stealth scan: "
$IPT -A bad_tcp_packets -p tcp --tcp-flags ALL FIN,URG,PSH -j DROP
$IPT -A bad_tcp_packets -p tcp --tcp-flags ALL SYN,RST,ACK,FIN,URG -j LOG --log-prefix "Stealth scan: "
$IPT -A bad_tcp_packets -p tcp --tcp-flags ALL SYN,RST,ACK,FIN,URG -j DROP
$IPT -A bad_tcp_packets -p tcp --tcp-flags SYN,RST SYN,RST -j LOG --log-prefix "Stealth scan: "
$IPT -A bad_tcp_packets -p tcp --tcp-flags SYN,RST SYN,RST -j DROP
$IPT -A bad_tcp_packets -p tcp --tcp-flags SYN,FIN SYN,FIN -j LOG --log-prefix "Stealth scan: "
$IPT -A bad_tcp_packets -p tcp --tcp-flags SYN,FIN SYN,FIN -j DROP
$IPT -A bad_tcp_packets -p tcp -j RETURN


### TCP & UDP ###

# DHCP
$IPT -A udp_inbound -p UDP -s 0/0 --source-port 67 --destination-port 68 -j ACCEPT

# HTTP Server
$IPT -A tcp_inbound -p TCP -s 0/0 --destination-port 80 --source-port 1024:65535 -j ACCEPT

# SSH Server
$IPT -A tcp_inbound -p TCP -s 0/0 --destination-port 22 -j ACCEPT

# Not matched, so return for logging
$IPT -A tcp_inbound -p TCP -j RETURN
$IPT -A udp_inbound -p UDP -j RETURN
$IPT -A tcp_outbound -p TCP -s 0/0 -j ACCEPT
$IPT -A udp_outbound -p UDP -s 0/0 -j ACCEPT


###############################################################################
#
# INPUT Chain
#

echo "Process INPUT chain ..."

# Allow all on localhost interface
$IPT -A INPUT -p ALL -i $LO_IFACE -j ACCEPT

# Drop bad packets
$IPT -A INPUT -p ALL -j bad_packets

# Accept established connections
$IPT -A INPUT -p ALL -i $LOCAL_IFACE -m state --state ESTABLISHED,RELATED -j ACCEPT

# Route the rest to the appropriate user chain
$IPT -A INPUT -p TCP -i $LOCAL_IFACE -j tcp_inbound
$IPT -A INPUT -p UDP -i $LOCAL_IFACE -j udp_inbound

# Drop broadcasts that get this far
$IPT -A INPUT -m pkttype --pkt-type broadcast -j DROP


###############################################################################
#
# OUTPUT Chain
#

echo "Process OUTPUT chain ..."

# Localhost
$IPT -A OUTPUT -p ALL -s $LO_IP -j ACCEPT
$IPT -A OUTPUT -p ALL -o $LO_IFACE -j ACCEPT

# DNS
$IPT -A OUTPUT -p UDP --dport 53 -m state --state NEW -j ACCEPT
$IPT -A OUTPUT -p TCP --dport 53 -m state --state NEW -j ACCEPT

# SSH
$IPT -A OUTPUT -p TCP --dport 22 -m state --state NEW -j ACCEPT

# HTTP
$IPT -A OUTPUT -p TCP --dport 80 -m state --state NEW -j ACCEPT

# Accept established outbound connections
$IPT -A OUTPUT -m state --state RELATED,ESTABLISHED -j ACCEPT

# Log packets that still don't match
$IPT -A OUTPUT -m limit --limit 3/minute --limit-burst 3 -j LOG --log-prefix "OUTPUT packet died: "

exit 0
