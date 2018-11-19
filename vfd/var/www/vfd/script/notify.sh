#!/bin/bash
cd `dirname $0`
. ./vf_display.sh

declare -x LANG="en_US.UTF-8"
zenity --info --title ${1:-" "} --text ${2:-" "} --timeout=3 --width 300
