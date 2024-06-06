#!/usr/bin/bash

if [[ "$#" -lt 3 ]]; then 
	echo "Too few arguments"
fi

printf -v date "%(%Y%m%d)T" -1

new_directory="backup_$date"

mkdir $new_directory

cd $new_directory
touch "name.log"
cd ..

for var in $@
do
	#echo $var
	if [ ! -e $var ]; then
		echo "The file does not exist"
	else
		cp $var "./$new_directory"
		#file_type=${var#*=}
		#new_name="${var%.*}"
		cd $new_directory
		echo "Old name: $var" >> name.log
		echo "New name: ${var}_${date}" >> name.log
		echo " " >> name.log
		mv $var "${var}_${date}"
		cd ..
	fi
done

cd $new_directory
location=`pwd`
echo "The process has completed. Backup directory is located at: $location "
