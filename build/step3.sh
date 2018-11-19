#!/bin/bash

printf "\nauto ens33\niface ens33 inet static\n    address 192.168.0.236\n    netmask 255.255.255.0\n    gateway 192.168.0.1\n\ndns-nameservers 192.168.0.1\n" >>/etc/network/interfaces
systemctl restart networking

apt-get -y install vim ssh cython python-m2crypto
apt-get -y install squashfs-tools compizconfig-settings-manager

#配置SSH服务
sed -i -e 's/^PermitRootLogin .*/PermitRootLogin yes/g' /etc/ssh/sshd_config
systemctl enable ssh
systemctl restart ssh

#禁用自动锁屏
gsettings set org.gnome.desktop.session idle-delay 0
gsettings set org.gnome.desktop.lockdown disable-lock-screen true

#禁用USB自动挂载
gsettings set org.gnome.desktop.media-handling automount false
gsettings set org.gnome.desktop.media-handling automount-open false 

#gsettings list-recursively org.gnome.desktop.wm.keybindings | perl -pe 's/(.*)\s*(\[.*?\])\s*$/$1\t$2\n/' | while IFS=$'\t' read -r key val; do gsettings set $key ['']; done
#gsettings list-recursively org.gnome.desktop.wm.keybindings | awk '{print "gsettings set "$1" "$2" \""$3"\""}'
gsettings set org.compiz.integrated show-hud "['']"

#以下是Navigation标签
gsettings set org.gnome.desktop.wm.keybindings move-to-workspace-1 []
gsettings set org.gnome.desktop.wm.keybindings move-to-workspace-2 []
gsettings set org.gnome.desktop.wm.keybindings move-to-workspace-3 []
gsettings set org.gnome.desktop.wm.keybindings move-to-workspace-4 []
gsettings set org.gnome.desktop.wm.keybindings move-to-workspace-5 []
gsettings set org.gnome.desktop.wm.keybindings move-to-workspace-6 []
gsettings set org.gnome.desktop.wm.keybindings move-to-workspace-7 []
gsettings set org.gnome.desktop.wm.keybindings move-to-workspace-8 []
gsettings set org.gnome.desktop.wm.keybindings move-to-workspace-9 []
gsettings set org.gnome.desktop.wm.keybindings move-to-workspace-10 []
gsettings set org.gnome.desktop.wm.keybindings move-to-workspace-11 []
gsettings set org.gnome.desktop.wm.keybindings move-to-workspace-12 []
gsettings set org.gnome.desktop.wm.keybindings move-to-workspace-left []
gsettings set org.gnome.desktop.wm.keybindings move-to-workspace-right []
gsettings set org.gnome.desktop.wm.keybindings move-to-workspace-up []
gsettings set org.gnome.desktop.wm.keybindings move-to-workspace-down []
gsettings set org.gnome.desktop.wm.keybindings move-to-workspace-last []
gsettings set org.gnome.desktop.wm.keybindings move-to-corner-nw []
gsettings set org.gnome.desktop.wm.keybindings move-to-corner-sw []
gsettings set org.gnome.desktop.wm.keybindings move-to-corner-ne []
gsettings set org.gnome.desktop.wm.keybindings move-to-corner-se []
gsettings set org.gnome.desktop.wm.keybindings move-to-side-w []
gsettings set org.gnome.desktop.wm.keybindings move-to-side-e []
gsettings set org.gnome.desktop.wm.keybindings move-to-side-n []
gsettings set org.gnome.desktop.wm.keybindings move-to-side-s []
gsettings set org.gnome.desktop.wm.keybindings move-to-center []
gsettings set org.gnome.desktop.wm.keybindings move-to-monitor-left []
gsettings set org.gnome.desktop.wm.keybindings move-to-monitor-right []
gsettings set org.gnome.desktop.wm.keybindings move-to-monitor-up []
gsettings set org.gnome.desktop.wm.keybindings move-to-monitor-down []

gsettings set org.gnome.desktop.wm.keybindings switch-to-workspace-1 []
gsettings set org.gnome.desktop.wm.keybindings switch-to-workspace-2 []
gsettings set org.gnome.desktop.wm.keybindings switch-to-workspace-3 []
gsettings set org.gnome.desktop.wm.keybindings switch-to-workspace-4 []
gsettings set org.gnome.desktop.wm.keybindings switch-to-workspace-5 []
gsettings set org.gnome.desktop.wm.keybindings switch-to-workspace-6 []
gsettings set org.gnome.desktop.wm.keybindings switch-to-workspace-7 []
gsettings set org.gnome.desktop.wm.keybindings switch-to-workspace-8 []
gsettings set org.gnome.desktop.wm.keybindings switch-to-workspace-9 []
gsettings set org.gnome.desktop.wm.keybindings switch-to-workspace-10 []
gsettings set org.gnome.desktop.wm.keybindings switch-to-workspace-11 []
gsettings set org.gnome.desktop.wm.keybindings switch-to-workspace-12 []
gsettings set org.gnome.desktop.wm.keybindings switch-to-workspace-left []
gsettings set org.gnome.desktop.wm.keybindings switch-to-workspace-right []
gsettings set org.gnome.desktop.wm.keybindings switch-to-workspace-up []
gsettings set org.gnome.desktop.wm.keybindings switch-to-workspace-down []
gsettings set org.gnome.desktop.wm.keybindings switch-to-workspace-last []

gsettings set org.gnome.desktop.wm.keybindings maximize []
gsettings set org.gnome.desktop.wm.keybindings minimize []
gsettings set org.gnome.desktop.wm.keybindings unmaximize []
gsettings set org.gnome.desktop.wm.keybindings maximize-horizontally []
gsettings set org.gnome.desktop.wm.keybindings maximize-vertically []


gsettings set org.gnome.desktop.wm.keybindings switch-input-source []
gsettings set org.gnome.desktop.wm.keybindings switch-applications []
gsettings set org.gnome.desktop.wm.keybindings switch-windows []
gsettings set org.gnome.desktop.wm.keybindings switch-panels []
gsettings set org.gnome.desktop.wm.keybindings switch-group []
gsettings set org.gnome.desktop.wm.keybindings switch-input-source-backward []
gsettings set org.gnome.desktop.wm.keybindings switch-applications-backward []
gsettings set org.gnome.desktop.wm.keybindings switch-windows-backward []
gsettings set org.gnome.desktop.wm.keybindings switch-panels-backward []
gsettings set org.gnome.desktop.wm.keybindings switch-group-backward []

gsettings set org.gnome.desktop.wm.keybindings cycle-windows []
gsettings set org.gnome.desktop.wm.keybindings cycle-panels []
gsettings set org.gnome.desktop.wm.keybindings cycle-group []
gsettings set org.gnome.desktop.wm.keybindings cycle-windows-backward []
gsettings set org.gnome.desktop.wm.keybindings cycle-panels-backward []
gsettings set org.gnome.desktop.wm.keybindings cycle-group-backward []

#以下是Typing标签
gsettings set org.gnome.desktop.wm.keybindings toggle-above []
gsettings set org.gnome.desktop.wm.keybindings toggle-maximized []
gsettings set org.gnome.desktop.wm.keybindings toggle-fullscreen []
gsettings set org.gnome.desktop.wm.keybindings toggle-on-all-workspaces []
gsettings set org.gnome.desktop.wm.keybindings toggle-shaded []

gsettings set org.gnome.desktop.wm.keybindings begin-move []
gsettings set org.gnome.desktop.wm.keybindings begin-resize []

#以下是Windows标签
gsettings set org.gnome.desktop.wm.keybindings activate-window-menu []

gsettings set org.gnome.desktop.wm.keybindings panel-main-menu []
gsettings set org.gnome.desktop.wm.keybindings panel-run-dialog []
gsettings set org.gnome.desktop.wm.keybindings always-on-top []
gsettings set org.gnome.desktop.wm.keybindings raise []
gsettings set org.gnome.desktop.wm.keybindings lower []
gsettings set org.gnome.desktop.wm.keybindings raise-or-lower []
gsettings set org.gnome.desktop.wm.keybindings show-desktop []
gsettings set org.gnome.desktop.wm.keybindings set-spew-mark []
gsettings set org.gnome.desktop.wm.keybindings close []


#以下是Launchers标签
gsettings set org.gnome.settings-daemon.plugins.media-keys help ''
gsettings set org.gnome.settings-daemon.plugins.media-keys calculator ''
gsettings set org.gnome.settings-daemon.plugins.media-keys email ''
gsettings set org.gnome.settings-daemon.plugins.media-keys terminal ''
gsettings set org.gnome.settings-daemon.plugins.media-keys www ''
gsettings set org.gnome.settings-daemon.plugins.media-keys home ''
gsettings set org.gnome.settings-daemon.plugins.media-keys search ''

#以下是Screenshots标签
gsettings set org.gnome.settings-daemon.plugins.media-keys area-screenshot ''
gsettings set org.gnome.settings-daemon.plugins.media-keys window-screenshot ''
gsettings set org.gnome.settings-daemon.plugins.media-keys screenshot 'Print'
gsettings set org.gnome.settings-daemon.plugins.media-keys area-screenshot-clip ''
gsettings set org.gnome.settings-daemon.plugins.media-keys window-screenshot-clip ''
gsettings set org.gnome.settings-daemon.plugins.media-keys screenshot-clip ''

#以下是Sound and Media标签
gsettings set org.gnome.settings-daemon.plugins.media-keys volume-mute ''
gsettings set org.gnome.settings-daemon.plugins.media-keys volume-down ''
gsettings set org.gnome.settings-daemon.plugins.media-keys volume-up ''
gsettings set org.gnome.settings-daemon.plugins.media-keys media ''
gsettings set org.gnome.settings-daemon.plugins.media-keys play ''
gsettings set org.gnome.settings-daemon.plugins.media-keys pause ''
gsettings set org.gnome.settings-daemon.plugins.media-keys stop ''
gsettings set org.gnome.settings-daemon.plugins.media-keys previous ''
gsettings set org.gnome.settings-daemon.plugins.media-keys next ''
gsettings set org.gnome.settings-daemon.plugins.media-keys eject ''

#以下是System标签
gsettings set org.gnome.settings-daemon.plugins.media-keys logout ''
gsettings set org.gnome.settings-daemon.plugins.media-keys screensaver ''

#以下是Universal Access标签
gsettings set org.gnome.settings-daemon.plugins.media-keys magnifier ''
gsettings set org.gnome.settings-daemon.plugins.media-keys magnifier-zoom-in ''
gsettings set org.gnome.settings-daemon.plugins.media-keys magnifier-zoom-out ''
gsettings set org.gnome.settings-daemon.plugins.media-keys screenreader ''
gsettings set org.gnome.settings-daemon.plugins.media-keys on-screen-keyboard ''
gsettings set org.gnome.settings-daemon.plugins.media-keys increase-text-size ''
gsettings set org.gnome.settings-daemon.plugins.media-keys decrease-text-size ''
gsettings set org.gnome.settings-daemon.plugins.media-keys toggle-contrast ''

############################################
#
#以下没找到
#
############################################
gsettings set org.gnome.settings-daemon.plugins.media-keys control-center ''
gsettings set org.gnome.settings-daemon.plugins.media-keys video-out ''
gsettings set org.gnome.settings-daemon.plugins.media-keys screencast ''

reboot
