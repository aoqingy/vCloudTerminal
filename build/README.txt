*********************************************************
*
* （零）安装Ubuntu 16.04.3
*
*********************************************************
1. 安装Ubuntu 16.04.3


*********************************************************
*
* （壹）检出源代码
*
*********************************************************
2. 设置root密码
> echo -e "123456\n123456" | sudo passwd
[sudo] password for demo:
> su

3. 获取动态IP
> dhclient

4. 更新操作系统和设置
> rm /var/lib/dpkg/lock
> apt-get update
> apt-get dist-upgrade

5. 安装git软件
> apt-get -y install git

6. 检出源代码
> cd /home
> git clone ssh://aoqingyun@192.168.0.249:29418/virtclass/vClassTerminal.git


*********************************************************
*
* （贰）设置自动登录
*
*********************************************************
7. 设置root自动登录
> sed -i 's/^mesg n .*/tty -s \&\& mesg n/g' /root/.profile
> cat > /etc/lightdm/lightdm.conf << EOF
[Seat:*]
autologin-guest=false
autologin-user=root
autologin-user-timeout=0
autologin-session=lightdm-autologin
EOF

8. 重启系统
> reboot


*********************************************************
*
* （叁）准备初始环境
*
*********************************************************
9. 设置静态IP地址
> printf "\nauto ens33\niface ens33 inet static\n    address 192.168.0.236\n    netmask 255.255.255.0\n    gateway 192.168.0.1\n\ndns-nameservers 192.168.0.1\n" >>/etc/network/interfaces
> systemctl restart networking

10. 安装必需软件
> apt-get -y install vim ssh cython python-m2crypto
> apt-get -y install squashfs-tools compizconfig-settings-manager

11. 启用SSH服务
> sed -i 's/^PermitRootLogin .*/PermitRootLogin yes/g' /etc/ssh/sshd_config
> systemctl enable ssh
> systemctl restart ssh

12. 关闭屏幕锁定
> gsettings set org.gnome.desktop.session idle-delay 0
> gsettings set org.gnome.desktop.lockdown disable-lock-screen true

13. 禁用键盘快捷
> Keyboard
Shortcuts->Disable All Shortcuts

14. 重启系统
> reboot


*********************************************************
*
* （肆）配置浏览器
*
*********************************************************
15. 安装status-4-evar
> firefox https://addons.mozilla.org/en-US/firefox/addon/status-4-evar/

16. 安装new-tab-homepage
> firefox https://addons.mozilla.org/en-US/firefox/addon/new-tab-homepage/

17. 安装disable-f12-shortcut
> firefox https://addons.mozilla.org/en-US/firefox/addon/disable-f12-shortcut/

18. 禁用浏览器Remember History
General->Privacy->History->Never Remember History

19. 设置浏览器首页为localhost
General->Startup->Homepage->localhost

#> about:config
#browser.startup.homepage->localhost

#20. 不允许关闭最后一个窗口
#> about:config
#browser.tabs.closeWindowWithLastTab->false

#21. 禁用浏览器更新
#> about:config
#app.update.auto->false
#app.update.enabled->false
#app.update.staging.enabled->false

#22. 禁用插件更新
#> about:config
#extensions.update.autoUpdateDefault->false
#extensions.update.enabled->false

#23. 禁用浏览器缓存
#> about:config
#browser.cache.disk.enable->false
#browser.cache.memory.enable->false
#browser.cache.offline.enable->false


*********************************************************
*
* （伍）添加ICA关联
*
*********************************************************
24. 添加ICA关联
> dpkg -i /home/vClassTerminal/upgrade/update/deplist/deb/ica*.deb
> touch /tmp/empty.ica
> firefox file:///tmp/empty.ica
Open with "Citrix Receiver Engine (default)"
Check "Do this automatically for files like this from now on."


*********************************************************
*
* （陆）完成编译环境
*
*********************************************************
#
#这一步是不是可以不做？
#
25. 禁用Ubuntu任务栏
> CCSM (CompizConfig Settings Manager)
Window Management->Grid->Uncheck
Desktop->Unity Plugin->Uncheck

26. 安装全屏插件
> firefox https://addons.mozilla.org/en-US/firefox/addon/1659/


I would like to disable the Alt+Tab (or all of the Alt+ combinations) on my Ubuntu 12.04 LTS. I tried to disable at System preferences -> Keyboard shortcuts, but this method doesn't seem to be working. Later I tried to activate an own shortcut for Alt+Tab (like an overwriting attempt), without any success...
Is there a way to disable this with or without compiz?
Install CompizConfig Settings Manager, find the Ubuntu unity plugin, Switcher tab, Set Key to start switcher to disabled

https://bbs.archlinux.org/viewtopic.php?id=162768(KVM VGA-Passthrough using the new vfio-vga support in kernel =>3.9)
