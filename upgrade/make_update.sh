#!/bin/bash
#
#需要注意的是：如果进行完整升级，云终端的开机画面将变回Ubuntu的徽标
#
#如果需要生成部分模块的升级包，调用时加上一个参数，例如：
#make_update.sh partial
#

cd `dirname $0`

./tuning.sh

vfd_file=(`ls ./update/vfd/ | awk '/vfd_[0-9\.]*/{print $0}'`)
vfd_vdeb=${vfd_file/*_/}
vfd_ver=${vfd_vdeb/\.deb/}

rm -f ./update_*

update_list=(`ls -dF update/* | grep /$`)

if [ "$1" != "iso" ]; then
    to_select=(${update_list[@]})
    to_update=''

    while :
    do
        choosen=""

        for ((i=0;i<${#to_select[@]};++i))
        do
            printf "[$i]${to_select[$i]}\n"
        done
        printf "\n"
        read -p "Select package to be installed? [0-$((${#to_select[@]}-1))/a(ll)/r(edo)/f(inish)] " choosen
        echo
        case ${choosen} in
            [0-9]*)
                if [ "${choosen}" -le "$((${#to_select[@]}-1))" ];
                then
                    to_update=(${to_update[@]} ${to_select[${choosen}]})
                    to_select=(${to_select[@]:0:${choosen}} ${to_select[@]:$((choosen+1))})
                else
                    echo "Invalid Input!"
                fi
                ;;
            a|A)
                to_update=(${update_list[@]})
                break;;
            f|F)
                break;;
            r|R)
                unset to_update
                to_select=(${update_list[@]});;
            *)
                echo 'Invalid Input!';;
        esac
    done
    echo "To update: ${to_update[@]} "
    read -s -n 1 -p "Press any key to continue..." confirm
    echo
else
    to_update=(${update_list[@]})
fi

tar -czf - ${to_update[@]} update/update.sh | dd of=update_${vfd_ver}

eval md5sum update_${vfd_ver} >> ./MD5SUM
tar -czf update_${vfd_ver}.tgz ./update_${vfd_ver} ../changelog.txt ./MD5SUM
rm ./MD5SUM
rm -f update_${vfd_ver}

