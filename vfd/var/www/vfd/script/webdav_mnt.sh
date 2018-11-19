#!/bin/bash
# $1    username
# $2    password
# $3    serverip
cd `dirname $0`
umount /tmp/webdav
sed -i '/remote.php/d' /etc/fstab

openssl s_client -connect ${3}:443 -showcerts </dev/null 2>/dev/null | openssl x509 -outform PEM > /etc/davfs2/certs/certificate.pem
[[ `grep ^trust /etc/davfs2/davfs2.conf` ]] || {
    echo "trust_server_cert        /etc/davfs2/certs/certificate.pem" >> /etc/davfs2/davfs2.conf
}

mkdir -p /tmp/webdav
[[ `grep ${3} /etc/fstab` ]] || {
    eval echo "https://${3}/remote.php/webdav /tmp/webdav davfs noauto,user 0 1" >> /etc/fstab
}

echo ${2} | mount /tmp/webdav -o username=${1}

