#!/bin/bash

echo -e "123456\n123456" | sudo passwd

su

dhclient

rm /var/lib/dpkg/lock
apt-get update
apt-get dist-upgrade

apt-get -y install git

cd /home
git clone ssh://aoqingyun@192.168.0.249:29418/virtclass/vClassTerminal.git

reboot
