#!/bin/bash
cd `dirname $0`

mount -t ntfs /dev/$1 /mnt
cp $2 /mnt/virtfan.bat
umount /mnt
