#!/bin/bash

IMAGE_NAME="windows-7"
PARTITION_LIST="sdb1 sdb2"


if [ $(id -u) != 0 ]; then
    echo "[!] Error: You must be root to run this script..."
    exit 1
fi

mkdir -p /home/partimag && cd /home/partimag
udp-receiver --file ${IMAGE_NAME}.tar --interface enp0s3 --ttl 1 --nokbd
[ $? -eq 0 ] && echo "[ ] Udp-receiver is complete..."

if [ -s "${IMAGE_NAME}.tar" ]; then
    tar -xcf ${IMAGE_NAME}.tar
    ocs-sr -g auto -icrc -k1 -scr -j2 restoreparts "${IMAGE_NAME}" "${PARTITION_LIST}"
    [ $? -eq 0 ] && echo "[ ] Restore ${IMAGE_NAME} to ${PARTITION_LIST} successfully..."
fi

