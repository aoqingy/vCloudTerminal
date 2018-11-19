#!/bin/bash
#Powered by Ubuntu 16.04.3 desktop

cd `dirname $0`
#apt-get install -y ssh vim cython squashfs-tools compizconfig-settings-manager

ProductName="vClassTerminal"
IsoVersion=`awk '$1~/^Version/ {print $2}' ./vfd/DEBIAN/control`
IsoName="${ProductName}-${IsoVersion}"

function Main
{
    InstallPackage
}

function InstallPackage
{
    echo
    echo "**********************************************"
    echo "*"
    echo "* Updating..."
    echo "*"
    echo "**********************************************"
    echo
    apt-get update

    echo
    echo "**********************************************"
    echo "*"
    echo "* Removing..."
    echo "*"
    echo "**********************************************"
    echo
    #以下为可安全移除软件包
    apt-get -y remove firefox aisleriot checkbox-converged checkbox-gui cheese deja-dup gnome-mahjongg gnome-mines gnome-sudoku gnome-system-monitor libreoffice-avmedia-backend-gstreamer libreoffice-base-core libreoffice-calc libreoffice-common libreoffice-core libreoffice-draw libreoffice-gnome libreoffice-gtk libreoffice-help-en-us libreoffice-impress libreoffice-math libreoffice-ogltrans libreoffice-pdfimport libreoffice-style-breeze libreoffice-style-galaxy libreoffice-writer python3-uno rhythmbox rhythmbox-plugin-zeitgeist rhythmbox-plugins shotwell shotwell-common simple-scan system-config-printer-gnome thunderbird thunderbird-gnome-support thunderbird-locale-en thunderbird-locale-en-us transmission-gtk ubuntu-desktop xterm firefox-locale-de firefox-locale-en firefox-locale-es firefox-locale-fr firefox-locale-it firefox-locale-pt firefox-locale-ru firefox-locale-zh-hans gnome-power-manager gnome-user-share libunity-webapps0 onboard onboard-data remmina remmina-plugin-rdp remmina-plugin-vnc unity-control-center-signon unity-webapps-common unity-webapps-service webapp-container webbrowser-app xdiagnose activity-log-manager evince evince-common gnome-orca ibus ibus-table indicator-bluetooth language-selector-gnome seahorse ubuntu-release-upgrader-gtk unity-control-center update-manager update-notifier usb-creator-gtk vino apturl file-roller gnome-calendar gnome-system-log gucharmap im-config nautilus-share software-properties-gtk

    #以下为待验证移除软件包
    #apt-get -y remove bluez bluez-cups bluez-obexd python3-update-manager ghostscript ghostscript-x cups cups-browsed cups-bsd cups-client cups-common cups-daemon cups-ppdc cups-server-common python3-cups python3-cupshelpers

    apt-get -y autoremove

    echo
    echo "**********************************************"
    echo "*"
    echo "* Upgrading..."
    echo "*"
    echo "**********************************************"
    echo
    apt-get -y dist-upgrade

    echo
    echo "**********************************************"
    echo "*"
    echo "* Installing..."
    echo "*"
    echo "**********************************************"
    echo
    #以下从网络安装软件包
    apt-get -y install vim ssh cython python-m2crypto
    apt-get -y install compizconfig-settings-manager
    apt-get -y install sqlite3 nfs-common python-flask python-ldap python-hivex python-xmltodict python-psutil x11vnc virt-viewer ffmpeg clonezilla udpcast gawk xbindkeys xdotool expect libgstreamer0.10 libgstreamer-plugins-base0.10 sysv-rc-conf

    #以下为待整理软件包
    ##apt-get install libgksu2-0 fonts-wqy-microhei openssh-server ser2net socat python-qt4 python-pyparsing libgtk-vnc-2.0-0 libavcodec-ffmpeg56 libavutil-ffmpeg54 libgsm1 libswscale-dev libavcodec-dev libavformat-dev libgtk-3-dev valac "libusbredir*dev" bison flex libogg-dev libusb-1.0-0-dev liblz4-dev libgstreamermm-1.0-dev libsmartcardpp-dev libcacard-dev libvirt-dev libgtk-vnc-2.0-dev -y --force-yes
    ##apt-get -f install -y

    echo
    echo "**********************************************"
    echo "*"
    echo "* Cleaning up..."
    echo "*"
    echo "**********************************************"
    echo
    apt-get -y autoremove

    sleep 15
    reboot
}

Main
