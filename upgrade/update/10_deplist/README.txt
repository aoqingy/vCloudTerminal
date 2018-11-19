#以下是新版本添加的软件包
#记得在替换Linux内核相关包时，同时升级更新编译环境，再执行make-iso.sh
ssh vim firefox nfs-common
python-flask python-ldap python-hivex python-m2crypto python-xmltodict python-psutil
x11vnc virt-viewer ffmpeg
clonezilla udpcast gawk
xbindkeys xdotool
libgstreamer0.10 libgstreamer-plugins-base0.10 expect


用途如下：
ssh                            方便ssh到终端上进行操作
vim                            方便编辑终端上的文件
firefox                        浏览器
nfs-common                     系统保存到或恢复自远程NFS共享
python-flask                   终端软件框架
python-ldap                    终端软件中用来LDAP访问
python-m2crypto                终端软件中用于密码处理
python-xmltodict               终端软件中实现XML到字典转换
python-psutil
python-hivex                   终端软件中操作Windows注册表
x11vnc                         用于其他主机通过VNC访问本云终端（在远程控制时）
virt-viewer                    用于通过VNC连接其他主机（在屏幕广播/终端演示时）
ffmpeg                         进行视频播放
clonezilla                     用于保存和恢复磁盘或分区
udpcast                        在Clonezilla中用到
gawk                           在Clonezilla中必需
xbindkeys                      快捷键CTRL-ALT-SHIFT-T等
xdotool                        仿真鼠键操作（从云课堂刷新云终端？）
libgstreamer0.10               VMware客户端需要
libgstreamer-plugins-base0.10  VMware客户端需要
expect                         安装VMware客户端需要


#以下是从其他源获得的软件包
#icaclientWeb ctxusb
#drbl-chntpw
#freerdp2-x11 libfreerdp2 libfreerdp-client2 libwinpr2
icaclientWeb                   Citrix的Web客户端
ctxusb                         Citrix客户端USB访问

#以下是未知是否需要的软件包
sysv-rc-conf


#以下可能是不需要的软件包
virtinst ser2net socat nfs-client open-iscsi initramfs-tools initramfs-tools-bin xtightvncviewer bittorrent virt-manager git openssh-client cpu-checker seabios zlib1g fonts-wqy-microhei python-qt4 python-flask-babel python-setuptools


#以下可能是编译virt-viewer需要的包
bison flex valac libgksu2-0 python-pyparsing libswscale-dev libavcodec-dev libavformat-dev libgtk-3-dev libogg-dev libusb-1.0-0-dev liblz4-dev libgstreamermm-1.0-dev libsmartcardpp-dev libcacard-dev libvirt-dev libgtk-vnc-2.0-dev "libusbredir*dev"


#还有一些残余的软件包
>>>libboost-iostreams1.58.0_1.58.0+dfsg-5ubuntu3.1_amd64.deb
>>>libyajl2_2.1.0-2_amd64.deb

#另，virt-viewer是为h264目的而设的
