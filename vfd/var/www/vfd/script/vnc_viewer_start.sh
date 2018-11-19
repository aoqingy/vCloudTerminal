#!/bin/bash
cd `dirname $0`
. ./vf_display.sh

[[ -f /root/.vflock ]] && exit
#[[ `ps -ef |awk '$0 ~ /firefox/ && $0 !~ /awk/''{print $2}'` ]] || exit
[[ `ps -ef |awk '$0 ~ /remote-viewer.*:5900/ && $0 !~ /awk/''{print $2}'` ]] && exit

nic=`ls -l /sys/class/net/ |awk '$9 ~ /^e/''{print $9}'`
ip=`ifconfig ${nic} |awk -F'[:| ]' '/inet addr/''{print $13}'`

if [[ ${1} != ${ip} ]]
then
    remote-viewer -f -k vnc://${1}:5900 &
fi

