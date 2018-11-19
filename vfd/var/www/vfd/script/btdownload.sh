#!/bin/bash
cd `dirname $0`

killall btdownloadheadless
sleep 1
btdownloadheadless "$1" --saveas "$2" &> ../log/image.stat &

