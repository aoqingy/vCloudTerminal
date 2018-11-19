注意：files目录由压缩文件解压得到，但其中的文件都已更改：
1. uninstall.sh
2. rc.usbsrvd

内核文件即时编译得到，确保内核版本正确

服务启动：/etc/init.d/rc.usbsrvd start
服务停止：/etc/init.d/rc.usbsrvd stop
服务状态：如果PID文件/var/run/usbsrvd.pid存在，则说明服务已启动；否则说明服务已停止
