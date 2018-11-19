#!/bin/bash
cd `dirname $0`
. ./vf_display.sh

ffid=$(xdotool search --name firefox | tail -n1)
xdotool key --window $ffid F5
