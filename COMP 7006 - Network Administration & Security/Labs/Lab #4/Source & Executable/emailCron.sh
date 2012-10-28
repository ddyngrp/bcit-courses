###############################################################################
#
#!/bin/bash
#
# SOURCE FILE:	emailCron.sh
# 
# PROGRAM:     Automated Email using Crontab
# 
# DATE:        October 20, 2009
# 
# REVISIONS:   
# 
# DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
# 
# PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
# 
# NOTES: Presents the user with a menu interface, allowing them to specify a
#        a date and time for when to receive an email. The email is scheduled
#        via Linux's crontab.
#
###############################################################################

# The program's main menu
main_menu()
{
	clear
	cat << 'MAIN_MENU'
Welcome to Email Scheduler!
	1: Enter new email alert into crontab
	2: Display current crontab
	3: Delete current crontab
	4: Quit
MAIN_MENU
	echo -n 'Enter Menu Item and Press Return > '
	read input
	case ${input} in
		[1]) email_input;;
		[2]) echo
			crontab -l
			press_enter
			main_menu;;
		[3]) echo
			echo 'Deleting Crontab'
			crontab -r
			press_enter
			main_menu;;
		[4]) exit ;;
		*) echo
			echo "Unrecognized Choice: ${input}"
			press_enter
			main_menu;;
	esac
}

# Function to wait for the user to press enter
press_enter()
{
	echo -n 'Press Enter to Continue...'
	read rest
}

# Retrieve and validate email address input by user
email_input()
{
	clear
	echo -n 'Enter email address (Q to cancel): '
	read email
	case ${email} in
		*@?*.?*) time_input;;
		[Qq]) main_menu;;
		*) echo
			echo "${email} is invalid."
			press_enter
			email_input;;
	esac
}

# Request the time to start the email
time_input()
{
	clear

	# Minute Input
	while true
	do
		echo 'Format: "[0-59]" for a specific minute, "*" for any, "*/[0-59]" for every [0-59] minutes)'
		echo -n 'Enter the minute and/or frequency (Q to cancel): '
		read minute
		case ${minute} in
			[0-9]|[0-5][0-9]|\*|\*/[0-9]|\*/[0-5][0-9]) break ;; # Validate Input
			[Qq]) main_menu ;;
			*) echo
				echo 'Please enter a minute in the proper format.'
				press_enter;;
		esac
	done

	echo

	# Hour Input
	while true
	do
		echo 'Format: "[0-23]" for a specific hour, "*" for any, "*/[0-23]" for every [0-23] hours)'
		echo -n 'Enter the hour and/or frequency (Q to cancel): '
		read hour
		case ${hour} in
			[0-9]|1[0-9]|2[0-3]|\*|\*/[0-9]|\*/1[0-9]|\*/2[0-3]) break ;; # Validate Input
			[Qq]) main_menu ;;
			*) echo
				echo 'Please enter an hour in the proper format.'
				press_enter;;
		esac
	done

	echo

	# Day of Month Input
	while true
	do
		echo 'Format: "[1-31]" for a specific day of month, "*" for any, "*/[0-31]" for every [0-31] days)'
		echo -n 'Enter the day of month and/or frequency (Q to cancel): '
		read day
		case ${day} in
			[1-9]|[1-2][0-9]|3[0-1]|\*|\*/[1-9]|\*/[1-2][0-9]|\*/3[0-1]) break ;; # Validate Input
			[Qq]) main_menu ;;
			*) echo
				echo 'Please enter a minute in the proper format.'
				press_enter;;
		esac
	done

	echo

	# Month of Year Input
	while true
	do
		echo 'Format: "[1-12]" for a specific month, "*" for any, "*/[1-12]" for every [0-12] months)'
		echo -n 'Enter the month and/or frequency (Q to cancel): '
		read month
		case ${month} in
			[1-9]|1[0-2]|\*|\*/[1-9]|\*/1[0-2]) break ;; # Validate Input
			[Qq]) main_menu ;;
			*) echo
				echo 'Please enter a minute in the proper format.'
				press_enter;;
		esac
	done

	echo

	# Day of Week Input
	while true
	do
		echo 'Format: "[0-6]" for a specific day, "*" for any, "*/[0-6]" for every [0-6] m)'
		echo -n 'Enter the minute and/or frequency (Q to cancel): '
		read weekday
		case ${weekday} in
			[0-6]|\*|\*/[0-6]) break ;; # Validate Input
			[Qq]) main_menu ;;
			*) echo
				echo 'Please enter a minute in the proper format.'
				press_enter;;
		esac
	done

	attachment_input
}

# Request the attachment, if any
attachment_input()
{
	clear

	echo -n 'Enter a path and file name to attach to the email (enter for none): '
	read attachment
	if [ -z ${attachment} ]
		then
			crontab_insert "NO"
		else
			if [ -f ${attachment} ]
				then
					crontab_insert "YES"
				else
					echo
					echo 'File does not exist.'
					press_enter
					attachment_input
			fi
	fi
}

# Insert the new entry into the user's crontab
crontab_insert()
{
	clear

	echo -n 'Inserting entry into crontab: '
	if [ $1 = 'YES' ]
		then
			echo "$minute $hour $day $month $weekday uuencode $attachment $attachment | mail -s 'Crontab Email w/ Attachment' $email" >> /tmp/tabfile
		else
			echo "$minute $hour $day $month $weekday mail -s 'Crontab Email' $email < /dev/null" >> /tmp/tabfile
	fi

	crontab /tmp/tabfile
	echo

	press_enter
	main_menu
}

rm /tmp/tabfile # Make sure we have no tabfile
main_menu # Enter the main menu
