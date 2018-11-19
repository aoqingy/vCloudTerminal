#!/bin/bash
cd `dirname $0`

echo
echo "Start to install keybinding ..."
echo

#终端打开（包括切换）功能
cp -a ./script/* /usr/bin/
cp -a ./xbindkeysrc /root/.xbindkeysrc

echo "Finish keybinding installation."

