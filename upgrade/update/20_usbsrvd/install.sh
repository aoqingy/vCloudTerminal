#!/bin/bash
cd `dirname $0`

echo
echo "Start to install usbsrvd ..."
echo

mkdir -p /usr/local/usb-redirector/bin

#编译内核文件
KERNELDIR=/lib/modules/`uname -r`/build
cd ./files/modules/src/tusbd
make KERNELDIR=$KERNELDIR clean
make "USE_EHCI_FIX=n VHCI=n STUB=y" KERNELDIR=$KERNELDIR
cd -

#拷贝内核文件
cp ./files/modules/src/tusbd/tusbd.ko /usr/local/usb-redirector/bin/tusbd.ko
chmod 644 /usr/local/usb-redirector/bin/tusbd.ko

#拷贝相关文件
cp ./files/uninstall.sh /usr/local/usb-redirector/uninstall.sh
cp ./files/usbsrvd-srv /usr/local/usb-redirector/bin/usbsrvd
cp ./files/usbsrv /usr/local/usb-redirector/bin/usbsrv
chmod 744 /usr/local/usb-redirector/uninstall.sh
chmod 744 /usr/local/usb-redirector/bin/usbsrvd
chmod 755 /usr/local/usb-redirector/bin/usbsrv
ln -s /usr/local/usb-redirector/bin/usbsrv /usr/bin/usbsrv

cp ./files/rc.usbsrvd /etc/init.d/rc.usbsrvd
chmod 755 /etc/init.d/rc.usbsrvd

#以下命令设置开机启动rc.usbsrvd，运行顺序编号为99，KILL顺序编号为01
#这条命令在制作ISO时，在chroot中会报错Running in chroot, ignoring request.
#但是使用该ISO安装的系统中，开机启动项还是生效的(aoqingy)
#因为需要将usbsrvd服务的管理修改到界面上，而不是开机即运行，故注释掉该行
#update-rc.d rc.usbsrvd defaults 99 01

echo "Finish usbsrvd installation."

