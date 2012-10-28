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
#        - ALLOW INPUT/OUTPUT SSH packets
#        - ALLOW INPUT/OUTPUT WWW packets
#        - ALLOW OUTPUT DNS traffic
#        - ALLOW OUTPUT DHCP traffic
#        - DROP all INPUT traffic to port 80 from source port < 1024
#        - DROP all INPUT traffic to reserved port 0
#        - DROP all INPUT traffic from reserved port 0
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
INET_IFACE="eth0"

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

# inbound/outbound packets
$IPT -N inbound-acct
$IPT -N outbound-acct


###############################################################################
#
# INPUT Chain
#

echo "Process INPUT chain ..."

# Allow all on localhost interface
$IPT -A INPUT -p ALL -i $LO_IFACE -j ACCEPT

# Drop inbound to and from reserved port 0
$IPT -A INPUT -j DROP -p tcp --sport 0
$IPT -A INPUT -j DROP -p udp --sport 0
$IPT -A INPUT -j DROP -p tcp --dport 0
$IPT -A INPUT -j DROP -p udp --dport 0

# Drop bad packets
$IPT -A INPUT -p ALL -m state --state INVALID -j DROP
$IPT -A INPUT -p tcp ! --syn -m state --state NEW -j DROP
$IPT -A INPUT -p tcp --tcp-flags ALL NONE -j DROP
$IPT -A INPUT -p tcp --tcp-flags ALL ALL -j DROP
$IPT -A INPUT -p tcp --tcp-flags ALL FIN,URG,PSH -j DROP
$IPT -A INPUT -p tcp --tcp-flags ALL SYN,RST,ACK,FIN,URG -j DROP
$IPT -A INPUT -p tcp --tcp-flags SYN,RST SYN,RST -j DROP
$IPT -A INPUT -p tcp --tcp-flags SYN,FIN SYN,FIN -j DROP

# DHCP
$IPT -A INPUT -p UDP -s 0/0 --sport 67 --dport 68 -j ACCEPT

# Drop broadcasts that get this far
$IPT -A INPUT -m pkttype --pkt-type broadcast -j DROP

# Route the rest to the accounting rules
$IPT -A INPUT -p TCP -i $INET_IFACE -j inbound-acct

# HTTP
$IPT -A inbound-acct -p TCP -s 0/0 --dport 80 --sport 1024:65535 -j ACCEPT

# SSH
$IPT -A inbound-acct -p TCP -s 0/0 --dport 22 -j ACCEPT

# Allow established connections
$IPT -A INPUT -p ALL -i $INET_IFACE -m state --state ESTABLISHED,RELATED -j ACCEPT

###############################################################################
#
# FORWARD Chain
#

echo "Process FORWARD chain ..."

# Inbound accounting
$IPT -A FORWARD -i $INET_IFACE -m tcp -p TCP --dport 22 -j inbound-acct
$IPT -A FORWARD -i $INET_IFACE -m tcp -p TCP --dport 80 -j inbound-acct
$IPT -A FORWARD -i $INET_IFACE -m tcp -p TCP --sport 22 -j inbound-acct
$IPT -A FORWARD -i $INET_IFACE -m tcp -p TCP --sport 80 -j inbound-acct

# Outbound accounting
$IPT -A FORWARD -s 0/0 -m tcp -p TCP --dport 22 -j outbound-acct
$IPT -A FORWARD -s 0/0 -m tcp -p TCP --dport 80 -j outbound-acct
$IPT -A FORWARD -s 0/0 -m tcp -p TCP --sport 22 -j outbound-acct
$IPT -A FORWARD -s 0/0 -m tcp -p TCP --sport 80 -j outbound-acct

###############################################################################
#
# OUTPUT Chain
#

echo "Process OUTPUT chain ..."

# Localhost
$IPT -A OUTPUT -p ALL -s $LO_IP -j ACCEPT
$IPT -A OUTPUT -p ALL -o $LO_IFACE -j ACCEPT

# DHCP
$IPT -A OUTPUT -p UDP --dport 68 -m state --state NEW -j ACCEPT

# DNS
$IPT -A OUTPUT -p TCP --dport 53 -m state --state NEW -j ACCEPT
$IPT -A OUTPUT -p UDP --dport 53 -m state --state NEW -j ACCEPT

# Route the rest to the accounting rules
$IPT -A OUTPUT -p TCP -s 0/0 -j outbound-acct

# HTTP
$IPT -A outbound-acct -p TCP --sport 80 -j ACCEPT
$IPT -A outbound-acct -p TCP --dport 80 -j ACCEPT

# SSH
$IPT -A outbound-acct -p TCP --sport 22 -j ACCEPT
$IPT -A outbound-acct -p TCP --dport 22 -j ACCEPT

exit 0
