#!/bin/bash
cd `dirname $0`

echo
echo "Start to install systemd ..."
echo

cp ./vfenv.sh /usr/sbin/vfenv.sh
cp ./vfenv.service /lib/systemd/system/vfenv.service
ln -sf /lib/systemd/system/vfenv.service /etc/systemd/system/multi-user.target.wants/vfenv.service

echo "Finish systemd installation."


