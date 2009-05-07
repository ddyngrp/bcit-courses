while true
do    
	memory=`ps -o vsz= -C spry`
	if [ -n "$memory" ]
	then
		mem2="${memory} "
		memory=`echo $memory / 25000 | bc`
		i=0
		while [ $i -lt $memory ]
		do
			mem2="${mem2}="
			i=`echo $i + 1 | bc`
		done
		echo $mem2
		echo $mem2 >> log.txt
		i=0
	fi
done
