###############################################################################
#
#!/bin/bash
#
# SOURCE FILE: firewall.sh
# 
# PROGRAM:     Standalone firewall
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

# Program Locations
SYSCTL="/sbin/sysctl -w"
IPT="/sbin/iptables"
IPTS="/sbin/iptables-save"
IPTR="/sbin/iptables-restore"
IFCONFIG="/sbin/ifconfig"
ROUTE="/sbin/route"

# Internet Interface
INET_IFACE="eth0"
INET_IP="192.168.227.100"
INET_NET="192.168.227.0/24"
INET_BCAST="192.168.1.255"

# Local Interface Information
LOCAL_IFACE="eth1"
LOCAL_IP="10.0.0.1"
LOCAL_NET="10.0.0.0/8"
LOCAL_NETMASK="255.255.255.0"
LOCAL_BCAST="10.0.0.255"

# Client Interface Information
CLIENT_IFACE="eth0"
CLIENT_IP="10.0.0.100"
CLIENT_NETMASK="255.255.255.0"
CLIENT_BCAST="10.0.0.255"
CLIENT_GATEWAY=$LOCAL_IP

# Localhost Interface
LO_IFACE="lo"
LO_IP="127.0.0.1"

# Allowed TCP Ports
TCP_ALLOWED="22 53 80"

# Allowed UDP Ports
UDP_ALLOWED="53"

# Allowed ICMP types
ICMP_ALLOWED="8 11"

# Always Blocked
TCP_BLOCKED="32768:32775 137:139 111 515"
UDP_BLOCKED="32768:32775 137:139"


###############################################################################
#
# Load Modules
#
function modules {
	echo "Loading required stateful/NAT kernel modules..."

	/sbin/depmod -a
	/sbin/modprobe ip_tables
	/sbin/modprobe ip_conntrack
	/sbin/modprobe ip_conntrack_ftp
	/sbin/modprobe ip_conntrack_irc
	/sbin/modprobe iptable_nat
	/sbin/modprobe ip_nat_ftp
	/sbin/modprobe ip_nat_irc
}


###############################################################################
#
# Kernel Parameter Configuration
#
function kernel {
	echo "Configuring kernel parameters..."

	# Enable IPv4 forwarding.
	$SYSCTL net.ipv4.ip_forward="1"

	# Enables SYN flood protection
	$SYSCTL net.ipv4.tcp_syncookies="1"

	# Enables source validation by reversed path according to RFC1812
	$SYSCTL net.ipv4.conf.all.rp_filter="1"

	# Ignore all ICMP echo requests sent to the broadcast address
	$SYSCTL net.ipv4.icmp_echo_ignore_broadcasts="1"

	# Refuse source routed packets
	$SYSCTL net.ipv4.conf.all.accept_source_route="0"

	# Disable ICMP redirects
	$SYSCTL net.ipv4.conf.all.accept_redirects="0"

	# Don't send Redirect Messages
	$SYSCTL net.ipv4.conf.all.send_redirects="0"

	# Enable secure_redirects
	$SYSCTL net.ipv4.conf.all.secure_redirects="1"

	# Logs packets from impossible addresses
	$SYSCTL net.ipv4.conf.all.log_martians="1"
}


###############################################################################
#
# Flush Any Existing Rules or Chains
#
function flush {
	echo "Flushing Tables..."

	# Reset Default Policies
	$IPT -P INPUT ACCEPT
	$IPT -P FORWARD ACCEPT
	$IPT -P OUTPUT ACCEPT
	$IPT -t nat -P POSTROUTING ACCEPT
	$IPT -t nat -P OUTPUT ACCEPT
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

###############################################################################
#
# Rules Configuration
#
function rules {
	echo "Setting default policy to DROP..."

	# Set Policies
	$IPT -P INPUT DROP
	$IPT -P OUTPUT DROP
	$IPT -P FORWARD DROP
}

###############################################################################
#
# User-Specified Chains
#
# Reduce the number of rules each packet must traverse
function user_chains {

	echo "Create and populate custom rule chains ..."

	# Process bad packets
	$IPT -N bad_packets
	$IPT -N bad_tcp_packets

	# Outbound TCP, UDP & ICMP Rules
	$IPT -N tcp_outbound
	$IPT -N udp_outbound
	$IPT -N icmp_outbound

	##
	# bad_packets chain
	##

	# Drop all from external interface claiming a source of the local network
	$IPT -A bad_packets -p ALL -i $INET_IFACE -s $LOCAL_NET -j DROP

	# Drop INVALID packets immediately
	$IPT -A bad_packets -p ALL -m state --state INVALID -j DROP

	# Check the tcp packets for additional problems
	$IPT -A bad_packets -p tcp -j bad_tcp_packets

	# All good, so return
	$IPT -A bad_packets -p ALL -j RETURN


	##
	# bad_tcp_packets chain
	# All tcp packets will traverse this chain.
	##

	# Trust the internal network
	#$IPT -A bad_tcp_packets -p tcp -i $LOCAL_IFACE -j RETURN

	# Not a NEW SYN
	$IPT -A bad_tcp_packets -p tcp ! --syn -m state --state NEW -j DROP

	# Possible stealth scans
	$IPT -A bad_tcp_packets -p tcp ! --syn -m state --state NEW -j DROP
	$IPT -A bad_tcp_packets -p tcp --tcp-flags ALL NONE -j DROP
	$IPT -A bad_tcp_packets -p tcp --tcp-flags ALL ALL -j DROP
	$IPT -A bad_tcp_packets -p tcp --tcp-flags ALL FIN,URG,PSH -j DROP
	$IPT -A bad_tcp_packets -p tcp --tcp-flags ALL SYN,RST,ACK,FIN,URG -j DROP
	$IPT -A bad_tcp_packets -p tcp --tcp-flags SYN,RST SYN,RST -j DROP
	$IPT -A bad_tcp_packets -p tcp --tcp-flags SYN,FIN SYN,FIN -j DROP

	# All good, so return
	$IPT -A bad_tcp_packets -p tcp -j RETURN


	##
	# tcp_packets chain
	##

	# Enable allowed ports
	for tcp_port in $TCP_ALLOWED
	do
		$IPT -A tcp_outbound -p tcp -s $LOCAL_NET --dport $tcp_port -j ACCEPT
		$IPT -A tcp_outbound -p tcp -s $INET_IP --dport $tcp_port -j ACCEPT
	done

	# No match, so DROP
	$IPT -A tcp_outbound -p tcp -s $LOCAL_NET -j DROP
	$IPT -A tcp_outbound -p tcp -s $INET_IP -j DROP


	##
	# udp_packets chain
	##

	# Enable allowed ports
	for udp_port in $UDP_ALLOWED
	do
		$IPT -A udp_outbound -p udp -s $LOCAL_NET --dport $udp_port -j ACCEPT
		$IPT -A udp_outbound -p udp -s $INET_IP --dport $udp_port -j ACCEPT
	done

	# No match, so DROP
	$IPT -A udp_outbound -p udp -s $LOCAL_NET -j DROP
	$IPT -A udp_outbound -p udp -s $INET_IP -j DROP


	##
	# icmp_packets chain
	##

	# Enable allowed types
	for icmp_type in $ICMP_ALLOWED
	do
		$IPT -A icmp_outbound -p icmp -s $LOCAL_NET --icmp-type $icmp_type -j ACCEPT
		$IPT -A icmp_outbound -p icmp -s $INET_IP --icmp-type $icmp_type -j ACCEPT
	done

	# No match, so DROP
	$IPT -A icmp_outbound -p icmp -s $LOCAL_NET -j DROP
	$IPT -A icmp_outbound -p icmp -s $INET_IP -j DROP
}


###############################################################################
#
# INPUT Chain
#

function input {
	echo "Process INPUT chain..."

	# Allow all on localhost interface
	$IPT -A INPUT -p ALL -i $LO_IFACE -j ACCEPT

	# Drop bad packets
	$IPT -A INPUT -p ALL -j bad_packets

	# Rules for the private network (accessing gateway system itself)
	#$IPT -A INPUT -p ALL -i $LOCAL_IFACE -s $LOCAL_NET -j ACCEPT
	#$IPT -A INPUT -p ALL -i $LOCAL_IFACE -d $LOCAL_BCAST -j ACCEPT

	# Block specific ports in all cases
	for tcp_block in $TCP_BLOCKED
	do
		$IPT -A INPUT -p tcp -i $INET_IFACE --dport $tcp_block -j DROP
	done

	for udp_block in $UDP_BLOCKED
	do
		$IPT -A INPUT -p udp -i $INET_IFACE --dport $udp_block -j DROP
	done

	# Accept Established Connections
	$IPT -A INPUT -p ALL -i $INET_IFACE -m state --state ESTABLISHED,RELATED -j ACCEPT
}


###############################################################################
#
# FORWARD Chain
#
function forward {
	echo "Process FORWARD chain..."

	# Drop bad packets
	$IPT -A FORWARD -p ALL -j bad_packets

	# Accept fragments
	$IPT -A FORWARD -f -j ACCEPT

	# Accept TCP packets we want to forward from internal sources
	$IPT -A FORWARD -p tcp -i $LOCAL_IFACE -j tcp_outbound

	# Accept UDP packets we want to forward from internal sources
	$IPT -A FORWARD -p udp -i $LOCAL_IFACE -j udp_outbound

	# Accept ICMP packets we want to forward from internal sources
	$IPT -A FORWARD -p icmp -i $LOCAL_IFACE -j icmp_outbound

	# If not blocked, accept any other packets from the internal interface
	$IPT -A FORWARD -p ALL -i $LOCAL_IFACE -j ACCEPT

	# Deal with responses from the internet
	$IPT -A FORWARD -i $INET_IFACE -m state --state ESTABLISHED,RELATED -j ACCEPT
}


###############################################################################
#
# OUTPUT Chain
#
function output {
	echo "Process OUTPUT chain ..."

	# Drop bad packets
	$IPT -A OUTPUT -p ALL -j bad_packets

	# Localhost
	$IPT -A OUTPUT -p ALL -s $LO_IP -j ACCEPT
	$IPT -A OUTPUT -p ALL -o $LO_IFACE -j ACCEPT

	# To internal network
	$IPT -A OUTPUT -p ALL -s $LOCAL_IP -j ACCEPT
	$IPT -A OUTPUT -p ALL -o $LOCAL_IFACE -j ACCEPT

	# Block specific ports in all cases
	for tcp_block in $TCP_BLOCKED
	do
		$IPT -A OUTPUT -p tcp -o $INET_IFACE --dport $tcp_block -j DROP
	done

	for udp_block in $UDP_BLOCKED
	do
		$IPT -A OUTPUT -p udp -o $INET_IFACE --dport $udp_block -j DROP
	done

	# To internet
	$IPT -A OUTPUT -p tcp -o $INET_IFACE -j tcp_outbound
	$IPT -A OUTPUT -p udp -o $INET_IFACE -j udp_outbound
	$IPT -A OUTPUT -p icmp -o $INET_IFACE -j icmp_outbound

	# Allow established outbound
	$IPT -A OUTPUT -p ALL -o $INET_IFACE -m state --state NEW,ESTABLISHED -j ACCEPT
}


###############################################################################
#
# POSTROUTING chain
#
function postrouting {
	echo "Load rules for nat table ..."

	$IPT -t nat -A POSTROUTING -o $INET_IFACE -j SNAT --to-source $INET_IP
}


###############################################################################
#
# mangle table
#
function mangle {
	echo "Load rules for mangle table ..."

	# SSH
	$IPT -A PREROUTING -t mangle -p tcp --sport 22 -j TOS --set-tos Minimize-Delay
	$IPT -A OUTPUT -t mangle -p tcp --dport 22 -j TOS --set-tos Minimize-Delay

	# FTP
	$IPT  -A PREROUTING -t mangle -p tcp --sport 21 -j TOS --set-tos Minimize-Delay
	$IPT  -A OUTPUT -t mangle -p tcp --dport 21 -j TOS --set-tos Minimize-Delay

	# FTP Data
	$IPT  -A PREROUTING -t mangle -p tcp --sport 20 -j TOS --set-tos Maximize-Throughput
	$IPT  -A OUTPUT -t mangle -p tcp --dport 20 -j TOS --set-tos Maximize-Throughput
}

###############################################################################
# 
# Interface Configuration Section
#
###############################################################################
function client {
	echo "Configuring external client interface $CLIENT_IFACE..."
	$IFCONFIG $CLIENT_IFACE down
	$IFCONFIG $CLIENT_IFACE $CLIENT_IP netmask $CLIENT_NETMASK broadcast $CLIENT_BCAST
	$IFCONFIG $CLIENT_IFACE up
	$ROUTE add default gw $CLIENT_GATEWAY
}

function firewall {
	echo "Configuring internal firewall interface $LOCAL_IFACE..."
	$IFCONFIG $LOCAL_IFACE down
	$IFCONFIG $LOCAL_IFACE $LOCAL_IP netmask $LOCAL_NETMASK broadcast $LOCAL_BCAST
	$IFCONFIG $LOCAL_IFACE up
}

###############################################################################
# 
# Implementation Section
#
###############################################################################

# Save and Restore arguments
if [ "$1" = "save" ]
then
	echo "Saving firewall to `pwd`/iptables-save... "
	$IPTS > ./iptables-save
	echo "done"
	exit 0
elif [ "$1" = "restore" ]
then
	echo "Restoring firewall from `pwd`/iptables-save... "
	$IPTR < ./iptables-save
	echo "done"
	exit 0
elif [ "$1" = "client" ]
then
	client	# configure the client's external interface
	exit 0
elif [ "$1" = "start" ]
then
	echo -n "Starting firewall..."
	firewall	# configure the firewall's internal interface
	modules		# load kernel modules
	kernel		# set kernel network settings
	flush		# flush any existing tables
	rules		# set default policies
	user_chains	# create and populate user defined chains
	input		# process the INPUT chain
	forward		# process the FORWARD chain
	output		# process the OUTPUT chain
	postrouting	# process the POSTROUTING chain
	mangle		# mangle tables
	exit 0
elif [ "$1" = "stop" ]
then
	flush
	echo "Firewall completely flushed! WARNING: Now running with no firewall."
	exit 0
fi

echo "Usage: ./firewall.sh {start|stop|save|restore|client}
  start   - starts the firewall and configures $LOCAL_IFACE with the following settings:
            IP Address = $LOCAL_IP
            Netmask    = $LOCAL_NETMASK
            Broadcast  = $LOCAL_BCAST
  stop    - stops the firewall
  save    - saves current iptables rules to `pwd`/iptables-save
  restore - restures saved iptables rules from `pwd`/iptables-save
  client  - configures the client's $CLIENT_IFACE with the follwing settings:
            IP Address = $CLIENT_IP
            Netmask    = $CLIENT_NETMASK
            Broadcast  = $CLIENT_BCAST
            Gateway    = $CLIENT_GATEWAY"