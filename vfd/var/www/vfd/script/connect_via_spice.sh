#!/bin/bash
cd `dirname $0`
. ./vf_display.sh

pulseaudio -D

#vv_file_path=$1
remote-viewer.sh ${1}
