#!/bin/bash
cd `dirname $0`

echo
echo "Start to install firefox..."
echo

#复制编译环境的Firefox配置
mkdir -p /root/.mozilla
cp -a ./mozilla/* /root/.mozilla/                         #Generated in make_update.sh

#将Firefox目录备份下来，每次开机时还原
cp -a ./mozilla/firefox /var/

#准备开机自动执行脚本
cp -a ./myfirefox /usr/bin/myfirefox
mkdir -p /root/.config/autostart
cat > /root/.config/autostart/myfirefox.desktop << EOF
[Desktop Entry]
Type=Application
Exec=/usr/bin/myfirefox
Hidden=false
NoDisplay=false
X-GNOME-Autostart-enabled=true
Name[en_US]=Firefox
Name=Firefox
Comment[en_US]=
Comment=
EOF

cp -a ./mimeTypes.rdf /root/.mozilla/firefox/*.default/             #For what purpose? (aoqingy)
#cp -a ./extensions/* /root/.mozilla/firefox/*.default/extensions/  #Can be removed? (aoqingy)
cp -a ./firefox-addons/* /usr/lib/firefox-addons/

echo "Finish firefox installation."

