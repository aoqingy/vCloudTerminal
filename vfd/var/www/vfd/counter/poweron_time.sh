#!/bin/bash
cd `dirname $0`

date +%s > ./LAST_TIME
cur_time=`cat ./USE_TIME` 
let cur_time=${cur_time:-'0'}+300
echo ${cur_time} > ./USE_TIME
