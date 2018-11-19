#!/bin/bash
cd `dirname $0`
. ./vf_display.sh

[[ `ps -ef |awk '$0 ~ /xinput/ && $0 !~ /awk/''{print $2}'` ]] && exit

while :
do
    [[ `which xinput` ]] || break
    devices=(`xinput --list |awk -F= '{print $2}' |cut -f 1`)
    for list in ${devices[@]}
    do
        xinput set-int-prop ${list} "Device Enabled" 8 0
    done
done &
