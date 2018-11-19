*********************************************************
*
* （零）安装Ubuntu 16.04.3
*
*********************************************************
1. 安装Ubuntu 16.04.3


*********************************************************
*
* （壹）更新操作系统和设置
*
*********************************************************
2. 设置root密码
> echo -e "123456\n123456" | sudo passwd
[sudo] password for demo:
> su

3. 设置IP地址
> vim /etc/network/interfaces
> systemctl restart networking

4. 更新操作系统和设置
> #update-manager
> apt-get update
> rm /var/lib/dpkg/lock
> apt-get dist-upgrade

*********************************************************
*
* （贰）检查出代码
*
*********************************************************
5. 安装git软件
> apt-get -y install git

6. 检出源代码
> git clone ssh://aoqingyun@192.168.0.249:29418/virtclass/vClassTerminal.git


*********************************************************
*
* （叄）设置root自动登录
*
*********************************************************
#
#这个过程在代码中处理了，还要在编译环境中做吗？(aoqingy)
#
7. 设置root自动登录
> cat /root/.profile
# ~/.profile: executed by Bourne-compatible login shells.

if [ "$BASH" ]; then
  if [ -f ~/.bashrc ]; then
    . ~/.bashrc
  fi
fi

mesg n || true
> sed -i 's/^mesg n .*/tty -s \&\& mesg n/g' /root/.profile
> cat /root/.profile
# ~/.profile: executed by Bourne-compatible login shells.

if [ "$BASH" ]; then
  if [ -f ~/.bashrc ]; then
    . ~/.bashrc
  fi
fi

tty -s && mesg n

#
#这个过程在代码中处理了，还要在编译环境中做吗？(aoqingy)
#
> printf "[Seat:*]\nautologin-guest=false\nautologin-user=root\nautologin-user-timeout=0\nautologin-session=lightdm-autologin\n" >/etc/lightdm/lightdm.conf
> cat /etc/lightdm/lightdm.conf
[Seat:*]
autologin-guest=false
autologin-user=root
autologin-user-timeout=0
autologin-session=lightdm-autologin

8. 重启系统
> reboot


*********************************************************
*
* （肆）安装必需软件
*
*********************************************************
9. 安装必需软件
> apt-get -y install vim ssh cython m2crypto
> apt-get -y install squashfs-tools compizconfig-settings-manager

10. 启用SSH服务
> sed -i 's/^PermitRootLogin .*/PermitRootLogin yes/g' /etc/ssh/sshd_config
> systemctl enable ssh
> systemctl restart ssh


*********************************************************
*
* （伍）禁用相关功能
*
*********************************************************
11. 禁用键盘快捷
> gsettings list-recursively org.gnome.desktop.wm.keybindings | perl -pe 's/(.*)\s*(\[.*?\])\s*$/$1\t$2\n/' | while IFS=$'\t' read -r key val; do gsettings set $key ['']; done
> #gsettings set org.gnome.settings-daemon.plugins.media-keys active false      #运行这条命令会导致unity报错（aoqingy）

12. 关闭屏幕锁定
#
#这是不是可以转到代码里面做？(aoqingy)
#
> gsettings set org.gnome.desktop.session idle-delay 0
> gsettings set org.gnome.desktop.lockdown disable-lock-screen true
> (Replaced by the above) gsettings set org.gnome.desktop.screensaver lock-enabled false


*********************************************************
*
* （陆）配置浏览器
*
*********************************************************
#
#这个过程在代码中处理了，还要在编译环境中做吗？(aoqingy)
#
13. 设置开机自动运行Firefox
> mkdir -p /root/.config/autostart
> printf "[Desktop Entry]\nType=Application\nExec=firefox\nHidden=false\nNoDisplay=false\nX-GNOME-Autostart-enabled=true\nName[en_US]=Firefox\nName=Firefox\nComment[en_US]=\nComment=\n" >/root/.config/autostart/firefox.desktop

14. 安装disable-f12-shortcut
> firefox https://addons.mozilla.org/en-US/firefox/addon/disable-f12-shortcut/

15. 安装status-4-evar
> firefox https://addons.mozilla.org/en-US/firefox/addon/status-4-evar/

16. 安装new-tab-homepage
> firefox https://addons.mozilla.org/en-US/firefox/addon/new-tab-homepage/

#17. 安装checkcompatibility
#> firefox https://addons.mozilla.org/en-US/firefox/addon/checkcompatibility/

18. 设置浏览器首页为localhost
> about:config
browser.startup.homepage->localhost

19. 不允许关闭最后一个窗口
> about:config
browser.tabs.closeWindowWithLastTab->false

20. 禁用浏览器更新
> about:config
app.update.auto->false
app.update.enabled->false
app.update.staging.enabled->false

21. 禁用插件更新
> about:config
extensions.update.autoUpdateDefault->false
extensions.update.enabled->false

22. 禁用插件兼容性检查
#> about:config
#extensions.check-compatibility.saved.55.0->false
#extensionx.check-compatibility.saved.nightly->false

23. 禁用浏览器缓存
> about:config
browser.cache.disk.enable->false
browser.cache.memory.enable->false
browser.cache.offline.enable->false

24. 禁用浏览器Remember Password
> about:config
signon.rememberSignons->false

25. 禁用浏览器Remember History                                          #aoqingy
General->Privacy->History->Never Remember History


*********************************************************
*
* （柒）添加ICA关联
*
*********************************************************
26. 添加ICA关联
> dpkg -i /home/vClassTerminal/upgrade/update/deplist/deb/ica*.deb
> touch /tmp/empty.ica
> firefox file:///tmp/empty.ica
Open with "Citrix Receiver Engine (default)"
Check "Do this automatically for files like this from now on."


*********************************************************
*
* （捌）准备VMware环境
*
*********************************************************
#
#这个过程在代码中处理了，还要在编译环境中做吗？(aoqingy)
#
27. 准备VMware环境
> apt-get install /home/vClassTerminal/upgrade/update/deplist/deb/libgstreamer*.deb
> ln -s /usr/lib/x86_64-linux-gnu/libffi.so.6 /usr/lib/x86_64-linux-gnu/libffi.so.5
> ./VMware-Horizon-Client-4.6.0-6617224.x64.bundle --eulas-agreed --console


*********************************************************
*
* （捌）完成编译环境
*
*********************************************************
27. 禁用Ubuntu任务栏
> ccsm
Window Management->Grid->disable
Desktop->Unity Plugin->disable

28. 安装mfull
> firefox https://addons.mozilla.org/en-US/firefox/addon/mfull/

