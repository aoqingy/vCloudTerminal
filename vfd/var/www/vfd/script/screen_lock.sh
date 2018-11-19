#!/bin/bash
cd `dirname $0`
. ./vf_display.sh

#eog是一个窗口程序，并不返回，因此必须以后台方式运行
#[[ `which eog` ]] && {
#    eog -f ../static/img/bg-class-lock.jpg
#} || {
#    feh -F ../static/img/bg-class-lock.png
#}
#pid=(`ps -ef |awk '$0 ~ /eog/ && $0 !~ /awk/''{print $2}'`)
#[[ ${#pid[@]} -gt 0 ]] && exit
[[ `ps -ef |awk '$0 ~ /eog/ && $0 !~ /awk/''{print $2}'` ]] && exit

if [[ ${1} ]]
then
    cp ${1} /tmp/message.jpg
    eog -f /tmp/message.jpg &
fi
