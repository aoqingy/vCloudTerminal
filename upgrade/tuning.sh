#!/bin/bash
cd `dirname $0`
trap "echo ' Waiting ...'" INT

pack_deb()
{
    #删除保存在update/vfd子目录下以前生成的软件包
    rm -f ./update/vfd/vfd*.deb

    #获取版本号，计算安装包名称
    vfd_ver=`grep Version ../vfd/DEBIAN/control | cut -d: -f 2`
    vfd_ver=`echo ${vfd_ver}`
    echo ${vfd_ver} > ../workspace/counter/version
    pkgname="vfd_${vfd_ver}.deb"

    #在工作空间目录下进行编译，生成.so文件
    cd ../workspace/
    python setup.py build_ext --inplace

    #回到当前目录，删除编译过程中生成的临时文件
    cd -
    rm -rf ../workspace/build				#编译临时目录
    rm -rf ../workspace/*.c				#编译中间文件
    rm -rf ../workspace/main.so				#main.py需保留，删除main.so
    rm -rf ../workspace/vncserver.so			#vncserver.so需保留，删除vncserver.so
    mkdir workspace-backup
    rm -rf workspace-backup/*
    mv ../workspace/*.py workspace-backup/		#为打包临时移走源文件
    mv workspace-backup/main.py ../workspace/		#main.py需保留，故拷贝回去
    mv workspace-backup/vncserver.py ../workspace/	#vncserver.py需保留，故拷贝回去
    dpkg-deb -b ../vfd ./update/vfd/${pkgname}		#打包

    #恢复编码环境
    mv workspace-backup/*.py ../workspace/		#打包后恢复临时移走的源文件
    rm ../workspace/*.so				#删除打包过程中生成的so文件
    rm -rf workspace-backup

    dpkg -i ./update/vfd/vfd_*.deb
}

restart_flask()
{
    to_kill=""
    to_kill=(`ps -ef |awk '$0 ~ /vfd.pyc/ && $0 !~ /awk/''{print $2}'`)
    [[ ${to_kill} != '' ]] && {
        for list in ${to_kill[@]}
        do
            kill -9 ${list}
        done
    }
    python /var/www/vfd/vfd.pyc &> /dev/null &
}

pack_deb
restart_flask
#service apache2 restart

#local_env()
#{
#	apt-get install python-flask libgksu2-0 python-m2crypto fonts-wqy-microhei apache2 wakeonlan libapache2-mod-wsgi python-pip python-psutil python-xmltodict python-ldap x11vnc xbindkeys -y
#	pip install --upgrade pip
#	pip install flask-babel pyflakes
#}

#auto_plus_version()
#{
#	new_build_num=`awk -F'.' '/Version/{print $3+1}' ./vfd/DEBIAN/control`
#	sed -i "/^Version/s/\.[0-9]*$/\.${new_build_num}/g" ./vfd/DEBIAN/control
#}
