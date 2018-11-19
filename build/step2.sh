#!/bin/bash

sed -i 's/^mesg n .*/tty -s \&\& mesg n/g' /root/.profile
#printf "[Seat:*]\nautologin-guest=false\nautologin-user=root\nautologin-user-timeout=0\nautologin-session=lightdm-autologin\n" >/etc/lightdm/lightdm.conf
cat > /etc/lightdm/lightdm.conf << EOF
[Seat:*]
autologin-guest=false
autologin-user=root
autologin-user-timeout=0
autologin-session=lightdm-autologin
EOF

reboot
