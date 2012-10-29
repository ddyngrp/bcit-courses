while true
do
	clear
	 cat << 'MENU'
 	L..................................... list files in current directory
 	W.................................. list of users logged in
 	C.................................... Display current calendar
 	D.................................... Date and Time
 	E....................................  Edit file using vi
 	Q...................................  Quit
MENU
	echo '           Press letter for choice, then Return >'
	read ltr rest
	case ${ltr} in
		[Cc])	cal 1 2005;;
		[Dd])	date | awk '{print $1, $2,  $3  ",  " $6,  "  Time: "  $4}';;
		[Ll])	ls	;;
		[Ww])	who	;;
		[Qq])	exit	;;
		[Ee])	echo 	
			echo '	Enter file to edit >'
			read fn rest
			vi ${fn}	;;
		*)	echo; echo Unrecognized choice: ${ltr} ;;
	esac
	echo; echo ' Press Enter to continue.....'
	read rest
done
