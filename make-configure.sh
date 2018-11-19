#!/bin/bash
#Powered by Ubuntu 16.04.3 desktop

cd `dirname $0`
#apt-get install -y ssh vim cython squashfs-tools compizconfig-settings-manager

ProductName="vClassTerminal"
IsoVersion=`awk '$1~/^Version/ {print $2}' ./vfd/DEBIAN/control`
IsoName="${ProductName}-${IsoVersion}"

function Main
{
    ConfigureSystem
}

function ConfigureSystem
{
    #配置SSH
    sed -i -e 's/^PermitRootLogin .*/PermitRootLogin yes/g' /etc/ssh/sshd_config
    systemctl enable ssh
    systemctl restart ssh

    #屏幕锁定
    gsettings set org.gnome.desktop.session idle-delay 0
    gsettings set org.gnome.desktop.lockdown disable-lock-screen true

    #以下从本地安装软件包
    dpkg -i ./upgrade/update/10_deplist/deb.special/firefox*.deb

    #ICA关联
    touch /tmp/empty.ica
    firefox file:///tmp/empty.ica

    #FireFox插件
    firefox https://addons.mozilla.org/en-US/firefox/addon/disable-f12-shortcut/
    firefox https://addons.mozilla.org/en-US/firefox/addon/status-4-evar/
    firefox https://addons.mozilla.org/en-US/firefox/addon/1659/

    #生成安装包
    rm -rf ./upgrade/update/firefox/mozilla
    rm -rf ./upgrade/update/config/root/config
    cp -a ~/.mozilla ./upgrade/update/firefox/mozilla
    cp -a ~/.config ./upgrade/update/config/root/config
    ./upgrade/make_update.sh iso

    #安装
    cp -a ./upgrade/update_${IsoVersion}.tgz /
    tar xzf /update_${IsoVersion}.tgz -C /
    rm -f /update_${IsoVersion}.tgz

    mkdir -p /update/
    tar xzf /update_${IsoVersion} -C /update
    rm -f /MD5SUM
    rm -f /update_${IsoVersion}

    /update/update/update.sh
    rm -rf /update

    #GRUB超时
    sed -i -e 's/if \[ "\\\${timeout}" = 0 \]; then$/if \[ "\\\${timeout}" != 0 \]; then/g' /boot/grub/grub.cfg
    sed -i -e 's/set timeout=.*$/set timeout=0/g' /boot/grub/grub.cfg

    reboot
}

Main
