#!/bin/bash
cd `dirname $0`
. ./vf_display.sh

[[ -f /root/.vflock ]] && exit
[[ `ps -ef |awk '$0 ~ /ffplay/ && $0 !~ /awk/''{print $2}'` ]] && exit

if [[ ${1} ]]
then
    ffplay -fs ${1} -ss ${2:-0}
fi
