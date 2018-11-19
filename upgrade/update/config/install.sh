#!/bin/bash
cd `dirname $0`

echo
echo "Start to install config..."
echo

IsoVersion=`ls ../vfd/*.deb`
IsoVersion=${IsoVersion##*_}
IsoVersion=${IsoVersion//.deb}
ProductName="vClassTerminal"

#Removed for EFI GRUB
#echo "Generating /etc/issue..."
#cat > ./etc/issue << EOF
#${ProductName} ${IsoVersion} \n \l
#EOF

#echo "Genertating /etc/issue.net..."
#cat > ./etc/issue.net << EOF
#${ProductName} ${IsoVersion}
#EOF

#echo "Generating /etc/lsb-release..."
#cat > ./etc/lsb-release << EOF
#DISTRIB_ID=${ProductName}
#DISTRIB_RELEASE=${IsoVersion%.*}
#DISTRIB_CODENAME=trusty
#DISTRIB_DESCRIPTION="${ProductName} ${IsoVersion}"
#EOF

#echo "Generting /etc/os-release..."
#cat > ./etc/os-release << EOF
#NAME="${ProductName}"
#VERSION="${IsoVersion}"
#ID=vClassTerminal
#ID_LIKE=debian
#PRETTY_NAME="${ProductName} ${IsoVersion}"
#VERSION_ID="${IsoVersion%.*}"
#HOME_URL="http://www.virtfan.com/"
#SUPPORT_URL="http://support.virtfan.com/"
#BUG_REPORT_URL="http://support.virtfan.com/"
#EOF

echo "Overwritting /etc..."
mkdir -p /usr/sbin/virtfan
cp -a ./etc/* /etc/
sed -i 's/^dns=dnsmasq/#dns=dnsmasq/g' /etc/NetworkManager/NetworkManager.conf
#以下自动运行脚本根据当前语言更新公共路径名
rm -r /etc/xdg/autostart/user-dirs-update-gtk.desktop
rm -f /etc/init/tty[1-6].conf

cp -a ./applications/* /usr/share/applications/    #aoqingy

#复制编译环境的用户配置
mkdir -p /root/.config
cp -a ./root/config/* /root/.config/            #Generated in make_update.sh
cp -a ./root/profile /root/.profile

#只能把关闭屏幕锁定放到编译环境准备中做，因为其运行需要DISPLAY(aoqingy)
#gsettings set org.gnome.desktop.session idle-delay 0
#gsettings set org.gnome.desktop.lockdown disable-lock-screen true

echo "Modifying language list..."
#以下修改安装中语言选择的向导页
cp -a ./ubiquity/localechooser/languagelist.data.gz /usr/lib/ubiquity/localechooser/.
#以下为生成languagelist.data.gz的方法：
#cat > ./ubiquity/localechooser/languagelist.data << EOF
#0:C:C:No localization
#3:zh_CN:Chinese (Simplified):中文(简体)
#0:en:English:English
#EOF
#gzip -f ./ubiquity/localechooser/languagelist.data

echo "Commenting out release notes..."
#以下注释掉安装中显示的发行注记
cp -a ./debconf/templates.dat /var/cache/debconf/.

echo "Finish config installation."

