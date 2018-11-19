#!/bin/bash
chmod 600 ${1}
sed -i 's/^fullscreen=0/fullscreen=1/g' ${1}

#engine_ip=`awk -F'=' '/^host=/{print $2}' ${1}`
#engine_ip=${engine_ip%/\ }
#vm_name=`awk -F'=|:' '/^title=/{print $2}' ${1}`
#tmpsum=`echo -n $vm_name |sha512sum`
#tmpsum=${tmpsum:0:4}
#port=`echo $tmpsum | awk '{print strtonum("0x"$0)}'`
#socat /dev/ttyS0 tcp:${engine_ip}:${port} &
#sleep 1

#/usr/bin/remote-viewer --spice-shared-dir=/tmp/webdav ${1}
#[[ -f /opt/config-env.sh ]] && source /opt/config-env.sh
/usr/bin/remote-viewer ${1}
