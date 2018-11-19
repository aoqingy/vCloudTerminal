#!/bin/bash
cd `dirname $0`
. ./vf_display.sh

#有密码调用：-rfbauth /etc/x11vnc.pass
#无密码调用：不带任何参数
#要设置密码：x11vnc -storepasswd [PASSWORD] /etc/x11vnc.pass

SCRN_DISPLAY=`awk -F= '{print $2}' ./vf_display.sh`

if [[ `ps -ef | grep x11vnc | grep -v grep` ]]
then
    killall -9 x11vnc
fi

x11vnc -shared -forever $@ -display ${SCRN_DISPLAY} &
