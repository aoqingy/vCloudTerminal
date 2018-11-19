#!/bin/bash
cd `dirname $0`
. ./vf_display.sh

sleep 5

cat > /tmp/local.vv << EOF
[virt-viewer]
type=spice
host=127.0.0.1
port=$1
fullscreen=1
enable-smartcard=0
enable-usb-autoshare=1
EOF

remote-viewer /tmp/local.vv
