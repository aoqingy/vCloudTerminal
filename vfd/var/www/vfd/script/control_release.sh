#!/bin/bash
cd `dirname $0`
. ./vf_display.sh

pid=(`ps -ef |awk '$0 ~ /control_grab.sh/ && $0 !~ /awk/''{print $2}'`)
kill -9 ${pid[@]}
[[ `which xinput` ]] || break
devices=(`xinput --list |awk -F= '{print $2}' |cut -f 1`)
for list in ${devices[@]}
do
    xinput set-int-prop ${list} "Device Enabled" 8 1
done
