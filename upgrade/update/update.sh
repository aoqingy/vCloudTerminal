#!/bin/bash
cd `dirname $0`

mkdir -p /var/www/vfd/log/
log_file="/var/www/vfd/log/update-`date +%Y%m%d`.log"
touch ${log_file}
date >> ${log_file}

update_dirs=(`ls -d */`)		#aoqingy
for dir in ${update_dirs[@]}
do
	cd ${dir}
	bash ./install.sh &>> ${log_file}
	cd ..
done
