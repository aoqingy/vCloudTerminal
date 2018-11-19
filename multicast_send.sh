#!/bin/bash

IMAGE_NAME="windows-7"
PARTITION_LIST="sdb1 sdb2"
RECEIVER_NUM=2

if [ $(id -u) != 0 ]; then
    echo "[!] Error: You must be root to run this script..."
    exit 1
fi

mkdir -p /home/partimag && cd /home/partimag
ocs-sr -q2 -j2 -scs -z1 -i 1000000 saveparts "${IMAGE_NAME}" "${PARTITION_LIST}"
[ $? -eq 0 ] && echo "[ ] Save ${PARTITION_LIST} to ${IMAGE_NAME} successfully..."

if [ -d "${IMAGE_NAME}" ]; then
    tar -cvf ${IMAGE_NAME}.tar ${IMAGE_NAME}
    udp-sender --file ${IMAGE_NAME}.tar --interface enp0s3 --full-duplex --ttl 1 --min-receivers ${RECEIVER_NUM} --nokbd
    [ $? -eq 0 ] && echo "[ ] Udp-sender is complete..."
fi
