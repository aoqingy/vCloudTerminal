#!/bin/bash
cd `dirname $0`
. ./vf_display.sh

[[ `ps -ef |awk '$0 ~ /recordmydesktop/ && $0 !~ /awk/''{print $2}'` ]] && exit

recordmydesktop --no-sound --overwrite -o /home/screenrecord.ogv
