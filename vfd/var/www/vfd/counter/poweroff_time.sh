#!/bin/bash
cd `dirname $0`

if [[ -f ./initial ]]
then
	cur_time=`date +%s`
	echo ${cur_time} > ./LAST_TIME
	rm -f ./initial
else
	cur_time=`date +%s`
	last_time=`cat ./LAST_TIME`
	let poweroff_time=${cur_time}-${last_time}

	use_time=`cat ./USE_TIME`
	let use_time=${use_time}+${poweroff_time}

	echo ${use_time} > ./USE_TIME
	echo ${cur_time} > ./LAST_TIME
fi

