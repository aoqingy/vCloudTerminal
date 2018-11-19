#!/bin/bash
cd `dirname $0`
. ./vf_display.sh
[[ `ps -ef |grep xbindkeys |grep -v grep` ]] && {
    killall xbindkeys
}
[[ `grep 'Alt + Home' /root/.xbindkeysrc` ]] || {
    echo \"\" >> /root/.xbindkeysrc
    echo "  Alt + Home" >> /root/.xbindkeysrc
}
/usr/bin/xbindkeys -f /root/.xbindkeysrc

