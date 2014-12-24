#!/bin/sh
#
# This shell Backsup the directory you want to

#echo "changes saved"
#global variables to keep track of things in the code and some to compare.
flag=0
count=0
max=$4

# Uses the mail function provided from mail-hello.sh to send mail
mail ()
{
	echo "Hello $USER!!" > tmp-message
	echo >> tmp-message
	echo "Today is" `date`  >> tmp-message
	echo >> tmp-message
	echo "Sincerely," >> tmp-message
	echo "     Myself" >> tmp-message
	/usr/bin/mailx -s "mail-hello" $USER < tmp-message 
	echo "Message sent."

}

# checks to see which was the first directory created
rem ()
{
	counter=1
	while read line
	do
		if [ $counter -eq $max ]
			then
				echo "$line"

		fi	
	
		counter=`expr $counter + 1`
	done <Store.txt
}

#checks if Four arguments are provided
if [ $# -lt 4 ] 
	then
	  echo
	  echo "$0 needs at least four arguments to run this code"
	  echo "For Example: backupd.sh dir backupdir interval-secs max-backups"
	  echo ""
fi

if [ $# -eq 4 ]
	then
	  echo
	  echo "./Backup has four arguments"

#Checks if the paths provided are correct or not. If the interval and max backup is an integer or not.
	if [ ! -d $1 ]
		then
			echo "Directory provided does not exist."
			echo "Run code again"
			exit
	
	elif [ ! -d $2 ]
		then
			echo "Creating a Backup directory since it does not exist."
			mkdir -p $2

	elif [ $3 -eq $3 2> /dev/null ]
		 then
			echo "$3 is a number";
	else
		echo "Third argument '"$3"' is not a number, run the program again and input a number"
		exit;
	fi

	if [ $4 -eq $4 2> /dev/null ]
		 then
			echo "$4 is a number";
	else
		echo "Fourth argument '"$4"' is not a number, run the program again and input a number"
		exit;
	fi
	
#Checks if the directory has been modified or not. If it has then use cp function to copy it, increase the counter
#to compare it with maximum number of backup and send an mail.

	ls -lR $1 > ls-lR.last
	cp -R $1 "$2/BackupDir<`date +%Y-%m-%d-%k-%M-%S`>"
	count=`expr $count + 1`
	mail

	while [ "1" ]
	do
		sleep $3
		ls -lR $1 > ls-lR.new

		if `diff ls-lR.new ls-lR.last >/dev/null` ; 
		then
		  	echo "The files are not modified from last backup"
			echo
		else
			echo "The files have been modified, so they are getting backup again"

#In this if loop, it checks if the count has reached maximum number of backup, and if it has then delete oldest directory

			if [ $count -eq $max ]
			then	
				ls -t $2 > Store.txt
				hi=`rem`
#				echo "okay final check $hi"
				rm -r "$2/$hi"
				echo "removed an directory because it reached its maximum limit"
				echo
				count=`expr $count - 1`
			fi
#			echo "copy inside while"
			cp -R $1 "$2/BackupDir<`date +%Y-%m-%d-%k-%M-%S`>"
			count=`expr $count + 1`
			mv ls-lR.new ls-lR.last
			mail

		fi

	done

fi			