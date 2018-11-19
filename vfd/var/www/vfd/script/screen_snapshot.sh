#!/bin/bash
cd `dirname $0`
. ./vf_display.sh

SCRN_DISPLAY=`awk -F= '{print $2}' ./vf_display.sh`
SCRN_SIZE=`xdpyinfo  |awk -F' ' '/dimen/''{print $2}'`

ffmpeg -y -s ${SCRN_SIZE:-320x256} -f x11grab -i ${SCRN_DISPLAY} -vframes 1 ${1}
mogrify -format jpg -quality 100 -resize 320x256 ${1}
