#!/bin/bash
#Powered by Ubuntu 16.04.3 desktop

cd `dirname $0`
#apt-get install -y ssh vim cython squashfs-tools compizconfig-settings-manager

export IsoPath="/home/iso/"
export CustomPath="/home/custom/"
export SquashfsPath="${CustomPath}/squashfs-root/"
ProductName="vClassTerminal"
IsoVersion=`awk '$1~/^Version/ {print $2}' ./vfd/DEBIAN/control`
IsoName="${ProductName}-${IsoVersion}"

function Main
{
    MakeUpdate
    CopyISO
    CustomISO
    UnSquashfs
    CustomSquashfs
    MkSquashfs
    MakeISO
}

function MakeUpdate
{
    rm -rf ./upgrade/update/firefox/mozilla
    rm -rf ./upgrade/update/config/root/config
    cp -a ~/.mozilla ./upgrade/update/firefox/mozilla
    cp -a ~/.config ./upgrade/update/config/root/config
    ./upgrade/make_update.sh iso
}

function CopyISO
{
    umount /mnt
    mount /dev/cdrom /mnt
    [ $? == 0 ] || exit 0
    rm -rf ${IsoPath}
    mkdir -p ${IsoPath}
    cp -a /mnt/* ${IsoPath}
    cp -a /mnt/.disk ${IsoPath}
}

function CustomISO
{
    cp -a ./upgrade/iso/autorun.inf ${IsoPath}/
    cp -a ./upgrade/iso/virtfan.ico ${IsoPath}/
    #cp -r ./upgrade/iso/boot/grub/* ${IsoPath}/boot/grub/.	#EFI?
    cp -r ./upgrade/iso/isolinux/* ${IsoPath}/isolinux/.
    echo 'http://www.virtfan.com' > ${IsoPath}/.disk/release_notes_url
    sed -i -e 's/Ubuntu 16.04.3/'${ProductName}' '${IsoVersion}'/g' ${IsoPath}/.disk/info
    cp ./upgrade/iso/initrd.lz ${IsoPath}/casper/initrd.lz
    # 如何定制initrd.lz：
    # lzma -dc -S .lz ../initrd.lz | cpio -id
    # custom initrd.lz files -- ./usr/share/plymouth/
    # find . | cpio --quiet --dereference -o -H newc | lzma -7 > ../initrd.lz
    rm -f ${IsoPath}/wubi.exe
    rm -f ${IsoPath}/ubuntu
}

function UnSquashfs
{
    rm -rf ${CustomPath} 
    mkdir -p ${CustomPath} 
    mv ${IsoPath}/casper/filesystem.squashfs ${CustomPath}
    cd ${CustomPath}
    unsquashfs filesystem.squashfs
    rm filesystem.squashfs
    cd -    #回到工作目录，为后续定制SQUASHFS做准备
}

function CustomSquashfs
{
    [[ `mount | grep ${SquashfsPath}proc`    ]] || mount --bind /proc     ${SquashfsPath}/proc
    [[ `mount | grep ${SquashfsPath}run`     ]] || mount --bind /run      ${SquashfsPath}/run
    [[ `mount | grep ${SquashfsPath}sys`     ]] || mount --bind /sys      ${SquashfsPath}/sys
    [[ `mount | grep ${SquashfsPath}dev`     ]] || mount --bind /dev      ${SquashfsPath}/dev
    cp -a /proc/mounts ${SquashfsPath}/etc/mtab

    echo
    echo "**********************************************"
    echo "*"
    echo "* Updating..."
    echo "*"
    echo "**********************************************"
    echo

    cp -a ./workspace/sources.list ${SquashfsPath}/etc/apt/
    cp -a ./workspace/virtfan.list ${SquashfsPath}/etc/apt/sources.list.d/
    chroot ${SquashfsPath} apt-get update

    echo
    echo "**********************************************"
    echo "*"
    echo "* Removing..."
    echo "*"
    echo "**********************************************"
    echo

    #以下为可安全移除软件包
    chroot ${SquashfsPath} apt-get -y remove firefox aisleriot checkbox-converged checkbox-gui cheese deja-dup gnome-mahjongg gnome-mines gnome-sudoku gnome-system-monitor libreoffice-avmedia-backend-gstreamer libreoffice-base-core libreoffice-calc libreoffice-common libreoffice-core libreoffice-draw libreoffice-gnome libreoffice-gtk libreoffice-help-en-us libreoffice-impress libreoffice-math libreoffice-ogltrans libreoffice-pdfimport libreoffice-style-breeze libreoffice-style-galaxy libreoffice-writer python3-uno rhythmbox rhythmbox-plugin-zeitgeist rhythmbox-plugins shotwell shotwell-common simple-scan system-config-printer-gnome thunderbird thunderbird-gnome-support thunderbird-locale-en thunderbird-locale-en-us transmission-gtk ubuntu-desktop xterm firefox-locale-de firefox-locale-en firefox-locale-es firefox-locale-fr firefox-locale-it firefox-locale-pt firefox-locale-ru firefox-locale-zh-hans gnome-power-manager gnome-user-share libunity-webapps0 onboard onboard-data remmina remmina-plugin-rdp remmina-plugin-vnc unity-control-center-signon unity-webapps-common unity-webapps-service webapp-container webbrowser-app xdiagnose activity-log-manager evince evince-common gnome-orca ibus ibus-table indicator-bluetooth language-selector-gnome seahorse ubuntu-release-upgrader-gtk unity-control-center update-manager update-notifier usb-creator-gtk vino apturl file-roller gnome-calendar gnome-system-log gucharmap im-config nautilus-share software-properties-gtk
    #安装并运行BootUp Manager（bum）后可以发现以下服务应该可以被移除(aoqingy)
    chroot ${SquashfsPath} apt-get -y remove whoopsie cups cups-browsed thermald irqbalance kerneloops pptp-linux brltty

    #以下为待验证移除软件包
    #chroot ${SquashfsPath} apt-get -y remove bluez bluez-cups bluez-obexd python3-update-manager ghostscript ghostscript-x cups cups-browsed cups-bsd cups-client cups-common cups-daemon cups-ppdc cups-server-common python3-cups python3-cupshelpers

    chroot ${SquashfsPath} apt-get -y autoremove

    echo
    echo "**********************************************"
    echo "*"
    echo "* Upgrading..."
    echo "*"
    echo "**********************************************"
    echo

    chroot ${SquashfsPath} apt-get -y dist-upgrade
    if [ $? != 0 ]; then
        echo "Failed to upgrade packages!"
        exit
    fi

    echo
    echo "**********************************************"
    echo "*"
    echo "* Installing..."
    echo "*"
    echo "**********************************************"
    echo

    #以下从网络安装软件包
    chroot ${SquashfsPath} apt-get -y install ssh vim sqlite3 nfs-common python-flask python-ldap python-hivex python-m2crypto python-xmltodict python-psutil x11vnc virt-viewer ffmpeg clonezilla udpcast gawk xbindkeys xdotool expect sysv-rc-conf libgstreamer0.10 libgstreamer-plugins-base0.10 qemu-utils qemu-kvm socat freerdp bittorrent python-celery python-celery-common python-redis redis-server python-paramiko recordmydesktop

    if [ $? != 0 ]; then
        echo "Failed to install packages!"
        exit
    fi

    #以下为待整理软件包
    ##chroot ${SquashfsPath} apt-get install libgksu2-0 fonts-wqy-microhei openssh-server ser2net socat python-qt4 python-pyparsing libgtk-vnc-2.0-0 libavcodec-ffmpeg56 libavutil-ffmpeg54 libgsm1 libswscale-dev libavcodec-dev libavformat-dev libgtk-3-dev valac "libusbredir*dev" bison flex libogg-dev libusb-1.0-0-dev liblz4-dev libgstreamermm-1.0-dev libsmartcardpp-dev libcacard-dev libvirt-dev libgtk-vnc-2.0-dev -y --force-yes
    ##chroot ${SquashfsPath} apt-get -f install -y

    rm -rf ${SquashfsPath}/var/cache/apt/archives/*

    echo
    echo "**********************************************"
    echo "*"
    echo "* Cleaning up..."
    echo "*"
    echo "**********************************************"
    echo
    chroot ${SquashfsPath} apt-get -y autoremove

    echo
    echo "**********************************************"
    echo "*"
    echo "* Configuring..."
    echo "*"
    echo "**********************************************"
    echo
    cp -a ./upgrade/update_${IsoVersion}.tgz ${SquashfsPath}/
    tar xzf ${SquashfsPath}/update_${IsoVersion}.tgz -C ${SquashfsPath}/
    rm -f ${SquashfsPath}/update_${IsoVersion}.tgz

    mkdir -p ${SquashfsPath}/update/
    tar xzf ${SquashfsPath}/update_${IsoVersion} -C ${SquashfsPath}/update
    rm -f ${SquashfsPath}/MD5SUM
    rm -f ${SquashfsPath}/changelog.txt
    rm -f ${SquashfsPath}/update_${IsoVersion}

    cd ${SquashfsPath}/update
    chroot ${SquashfsPath} /update/update/update.sh
    rm -rf ${SquashfsPath}/update

    #chroot ${SquashfsPath} sed -i -e 's/if \[ "\\\${timeout}" = 0 \]; then$/if \[ "\\\${timeout}" != 0 \]; then/g' /etc/grub.d/30_os-prober
    #chroot ${SquashfsPath} sed -i -e 's/set timeout=.*$/set timeout=0/g' /etc/grub.d/30_os-prober
    #chroot ${SquashfsPath} sed -i -e 's/^GRUB_DISTRIBUTOR=.*$/GRUB_DISTRIBUTOR=ubuntu/g' /etc/default/grub
    #chroot ${SquashfsPath} update-grub

    rm -rf ${SquashfsPath}/etc/mtab
    umount ${SquashfsPath}/proc
    umount ${SquashfsPath}/run
    umount ${SquashfsPath}/sys
    umount ${SquashfsPath}/dev
}

function MkSquashfs
{
    cd ${CustomPath}
    mksquashfs squashfs-root filesystem.squashfs
    printf $(sudo du -sx --block-size=1 squashfs-root | cut -f1) > ./filesystem.size
    mv filesystem.s* ${IsoPath}/casper/
}

function MakeISO
{
    mkdir -p /home/${IsoName}
    rm -rf /home/${IsoName}/*
    cd ${IsoPath}
    find -type f -print0 | sudo xargs -0 md5sum | grep -v isolinux/boot.cat | sudo tee md5sum.txt
    #xorriso -as mkisofs -D -r -V "vClassTerminal" -cache-inodes -J -l -isohybrid-mbr isolinux/isohdpfx.bin -c isolinux/boot.cat -b isolinux/isolinux.bin -e boot/grub/efi.img -no-emul-boot -boot-load-size 4 -boot-info-table -eltorito-alt-boot -isohybrid-gpt-basdat -o /home/${IsoName}/${IsoName}.iso .
    mkisofs -D -r -V "vClassTerminal" -cache-inodes -J -l -b isolinux/isolinux.bin -c isolinux/boot.cat -no-emul-boot -boot-load-size 4 -boot-info-table -o /home/${IsoName}/${IsoName}.iso .

    cd /home/${IsoName}
    md5sum ${IsoName}.iso > MD5SUMS.txt
    cat > boot-test.sh << EOF
#!/bin/bash
apt-get install -y qemu-system-x86
qemu-img create -f qcow2 disk.img 10G
qemu-system-x86_64 -enable-kvm -smp 2,sockets=1 -m 2048 -boot order=dc -hda ./disk.img -cdrom ./${IsoName}.iso
EOF
    chmod +x boot-test.sh

    umount /mnt
}

Main
