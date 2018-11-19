#!/bin/bash
cd `dirname $0`
. ./vf_display.sh

[[ -f /root/.vflock ]] && exit
[[ `ps -ef |awk '$0 ~ /ffmpeg -i/ && $0 !~ /awk/''{print $2}'` ]] && exit
ffmpeg -i /dev/video0 -f rtsp rtsp://${1}:554/${2}.sdp

