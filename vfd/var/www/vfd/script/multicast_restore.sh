#!/bin/bash

ocs_file="$0"
ocs=`basename $ocs_file`
ocs_myself_id="$$"

ocs_ppid="$PPID"

confirm_before_clone="no"
ocs_sr_mode=""
gen_md5sum="no"
gen_sha1sum="no"
check_md5sum="no"
check_sha1sum="no"
gen_chksum_for_files_in_dev="no"
chk_chksum_for_files_in_dev="no"
chk_img_restoreable_mod_save="yes"
chk_img_restoreable_mod_restore="yes"


OCS_OPT=
udp_sender_extra_opt="--full-duplex"
USE_NTFSCLONE="no"
FORCE_TO_USE_DD="no"
create_part="yes"
restore_mbr="yes"
restore_prebuild_mbr="no"
rm_win_swap_hib="no"
select_img_in_client="no"
udpcast_stderr="/dev/null"
run_prerun_dir="no"
run_postrun_dir="no"


save_restore_error_log="no"
chk_tgt_disk_size_bf_mk_pt="yes"
update_efi_nvram=""

mcast_wait_time=""
n_clients=""
mcast_max_wait_time=""
imagedir="/home/partimag"
eth_for_multicast="enp0s3"
# ls /sys/class/net | grep -E '(enp|wlp).*' | head -1

DRBL_SCRIPT_PATH="${DRBL_SCRIPT_PATH:-/usr/share/drbl}"

. $DRBL_SCRIPT_PATH/sbin/drbl-conf-functions
. /etc/drbl/drbl-ocs.conf
. $DRBL_SCRIPT_PATH/sbin/ocs-functions

[ -e "/etc/ocs/ocs-live.conf" ] && . /etc/ocs/ocs-live.conf

usage() {
    echo "Usage:"
    echo "To restore image using multicast"
    echo "$ocs [OPTION] {multicast_restoredisk|multicast_restoreparts} IMAGE_NAME DEVICE"

    echo " --min-receivers      Automatically start as soon as a minimal number of receivers have connected."
    echo " --min-wait      Even when the necessary amount of receivers do have connected, still wait until t seconds since first receiver connection have passed."
    echo " --max-wait      When not enough receivers have connected (but at least one), start anyways when t seconds since first receiver connection have pased."

    echo " --mcast-port      Default ports to use for udpcast. Two ports are used: portbase and portbase+1. Thus, Portbase must be even. Default is $MULTICAST_PORT."
    echo " --interface      Network interface used to send out the data. Default is enp0s3."
}

parse_option() {
    while [ $# -gt 0 ]; do
        case "$1" in
            -t|--task)
                shift
                if [ -z "$(echo $1 | grep ^-.)" ]; then
                    task="$1"
                    shift
                fi
                [ -z "$task" ] && usage && exit 1
                ;;
            -o|--option)
                shift
                if [ -z "$(echo $1 | grep ^-.)" ]; then
                    option="$@"
                    shift $#
                fi
                [ -z "$option" ] && usage && exit 1
                ;;
            -n|--min-receivers)
                shift
                if [ -z "$(echo $1 | grep ^-.)" ]; then
                    n_clients="$1"
                    shift
                fi
                [ -z "$n_clients" ] && usage && exit 1
                ;;
            --min-wait)
                shift
                if [ -z "$(echo $1 | grep ^-.)" ]; then
                    mcast_wait_time="$1"
                    shift
                fi
                [ -z "$mcast_wait_time" ] && usage && exit 1
                ;;
            --max-wait)
                shift
                if [ -z "$(echo $1 | grep ^-.)" ]; then
                    mcast_max_wait_time="$1"
                    shift
                fi
                [ -z "$mcast_max_wait_time" ] && usage && exit 1
                ;;
            --mcast-port)
                shift
                if [ -z "$(echo $1 | grep ^-.)" ]; then
                    port="$1"
                    shift
                fi
                [ -z "$port" ] && usage && exit 1
                ;;
            --interface)
                shift
                if [ -z "$(echo $1 | grep ^-.)" ]; then
                    eth_for_multicast="$1"
                    shift
                fi
                [ -z "$eth_for_multicast" ] && usage && exit 1
                ;;
            -*) echo "${0}: ${1}: invalid option" >&2
                usage >& 2
                exit 2 ;;
            *)  break ;;
        esac
    done
}

multicast_restoreparts() {
    local tgt_dir="$1"
    local tgt_parts="$2"
    local part_is_lvm

    ipart=1
    port=$MULTICAST_PORT
    do_LVM_restore_feed="no"

    for partition in $tgt_parts; do
        hd_tmp="$(get_diskname $partition)"
        part_is_lvm="no"
        if [ -n "$(grep -Ew "$partition" $imagedir/$tgt_dir/lvm_vg_dev.list 2>/dev/null)" ]; then
            part_is_lvm="yes"
            continue
        fi
        udp_send_part_img $tgt_dir $partition $partition
    done

    if [ "$part_is_lvm" = "yes" ]; then
        do_LVM_restore_feed="yes"
        feed_LVM_multicast "$tgt_parts" $port
    fi
} # end of multicast_restoreparts

# multicast_restore -n min-clients -t multicast_restoredisk -o "img_name" "disk"
# multicast_restore -n min-clients -t multicast_restoreparts -o "img_name" "part1 part2"

check_if_root
parse_option $@

if [ -n "$(echo "$task" | grep -e "^multicast_restore")" ]; then
    OCS_OPT="$OCS_OPT --mcast-port $MULTICAST_PORT"
fi


if [ -n "$(echo "$task" | grep -e "^multicast_restore")" ]; then
    [ -n "$mcast_wait_time" ] && udpcast_hold_opt1="--min-wait $mcast_wait_time"
    [ -n "$n_clients" ] && udpcast_hold_opt2="--min-receivers $n_clients"
    [ -n "$mcast_max_wait_time" ] && udpcast_hold_opt3="--max-wait $mcast_max_wait_time"

    if [ -z "$udpcast_hold_opt1" -a -z "$udpcast_hold_opt2" -a -z "$udpcast_hold_opt3" ]; then
        echo "No time_to_wait, clients_to_wait or clients+time_to_wait option was found." | tee --append ${OCS_LOGFILE}
        echo "$msg_program_stop!" | tee --append ${OCS_LOGFILE}
        exit 1
    fi
fi

target_dir="$(echo $option | awk -F" " '{print $1}' | tr -d \")"
target_parts="$(echo $option | awk '{ for (i=2; i<=NF; i++) printf "%s ", $i; printf "\n"; }' | sed -e "s/^[[:space:]]*//" -e "s/[[:space:]]*$//" | tr -d \")"

case "$task" in
    "multicast_restoredisk")
        target_parts=""
        target_hd="$(< $imagedir/$target_dir/disk)"

        for ihd in $target_hd; do
            for partition in `cat $imagedir/$target_dir/parts`; do
                if [ -n "$(echo "$partition" | grep -iE "$ihd")" ]; then
                    target_parts="$target_parts $partition"
                fi
            done
        done

        target_parts="$(echo $target_parts | sed -e "s/^  *$//")"

        if [ -z "$target_parts" ]; then
            [ "$BOOTUP" = "color" ] && $SETCOLOR_FAILURE
            echo "No target partitions were found from image $target_dir!" | tee --append ${OCS_LOGFILE}
            echo "Failed to start $multi_broad_cast_prompt clone service for image $target_dir!" | tee --append ${OCS_LOGFILE}
            [ "$BOOTUP" = "color" ] && $SETCOLOR_NORMAL
            echo "$msg_program_stop!" | tee --append ${OCS_LOGFILE}
            exit 1
        fi
        multicast_restoreparts "$target_dir" "$target_parts"
        ;;

    "multicast_restoreparts")
        if [ -z "$target_parts" ]; then
            [ "$BOOTUP" = "color" ] && $SETCOLOR_FAILURE
            echo "No target partitions were found from image $target_dir!" | tee --append ${OCS_LOGFILE}
            echo "Failed to start $multi_broad_cast_prompt clone service for image $target_dir!" | tee --append ${OCS_LOGFILE}
            [ "$BOOTUP" = "color" ] && $SETCOLOR_NORMAL
            echo "$msg_program_stop!" | tee --append ${OCS_LOGFILE}
            exit 1
        fi
        multicast_restoreparts "$target_dir" "$target_parts"
        ;;
esac

#bash multicast_restore -n 1 -t multicast_restoreparts -o "centos-img" "sdb1 sdb2"

#ocs-sr -g auto -icrc -k1 -scr -j2 --mcast-port 2232 multicast_restoreparts "centos-img" "sdb1 sdb2"
