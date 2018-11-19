#!/bin/bash
cd `dirname $0`

echo
echo "Start to install vmware ..."
echo

#需要挂载devpts文件系统，否则无法安装
mount -t devpts devpts /dev/pts

#依赖组件，创建链接
ln -s /usr/lib/x86_64-linux-gnu/libffi.so.6 /usr/lib/x86_64-linux-gnu/libffi.so.5

#执行安装脚本
./vmware-client-auto-installer.sh

#在安装后会运行vmware守护进程，该进程需要被杀掉，否则不能正确制作ISO
#pkill -9 vmware  #在安装时不启动，就不需要杀死相关进程(aoqingy)
#pkill -9 dbus    #这条命令不能执行，否则会引起编译环境刷屏(aoqingy)

#这个文件本应该是个链接，在SquashFS里面不知为何变成了一个文件？(aoqingy)
[[ -f /usr/lib/vmware/view/vdpService/libmksvchanclient.so ]] && {
    rm /usr/lib/vmware/view/vdpService/libmksvchanclient.so
}

umount /dev/pts

echo "Finish vmware installation."
