#!/bin/bash
cd `dirname $0`
. ./vf_display.sh

pid=(`ps -ef |awk '$0 ~ /remote-viewer.*:5900/ && $0 !~ /awk/''{print $2}'`)
[[ ${pid} ]] && kill -9 ${pid[@]}
