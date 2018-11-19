#!/bin/bash
cd `dirname $0`

echo
echo "Start to install vfd ..."
echo

pids=(`lsof /var/lib/apt/lists/lock | awk '{print $2}'`)
tokill=(`for list in ${pids[@]}; do [[ ${list} =~ ^[0-9]*$ ]] && echo ${list}; done |uniq`)
for list in ${tokill[@]}; do kill -9 ${list}; done

dpkg -i ./vfd_*.deb

echo "Finish vfd installation."

