#!/bin/bash
cd `dirname $0`

echo
echo "Start to install software ..."
echo

echo "Installing deb..."
#dpkg -i ./deb.general/*.deb
#dpkg -i ./deb.general/gawk*.deb  #由于依赖关系，在前次安装时没有成功
dpkg -i ./deb.special/*.deb

#cp -a ./virt-viewer/* /
#[[ `grep '/opt/lib/' /etc/ld.so.conf` ]] || {
#    echo "include /opt/lib/" >> /etc/ld.so.conf
#}

echo "Finish software installation."

