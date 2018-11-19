#!/bin/bash

cd `dirname $0`

mount --bind /proc ${SquashfsPath}/proc
mount --bind /run ${SquashfsPath}/run
cp -a /proc/mounts ${SquashfsPath}/etc/mtab
chroot ${SquashfsPath} apt-get update
chroot ${SquashfsPath} apt-get install samba -y --force-yes
chroot ${SquashfsPath} mkdir -p ${SquashfsPath}/var/image
cp ./smb.conf  ${SquashfsPath}/etc/samba/smb.conf
chroot ${SquashfsPath} systemctl enable samba
umount ${SquashfsPath}/proc
umount ${SquashfsPath}/run
rm -rf ${SquashfsPath}/etc/mtab
