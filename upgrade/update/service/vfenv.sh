#!/bin/sh

#添加此项才能实现以root身份自动登录
sed -i 's/^autologin-user=.*/autologin-user=root/g' /etc/lightdm/lightdm.conf

exit 0
