#!/usr/bin/python
#-*-coding:utf-8 -*-
from const      import *
from task       import *
from image      import *
from course     import * 
from bloader    import *
#from partition  import *
from permit     import *
from usbredir   import *
from router     import *
from virtapi    import *
from utility    import *
from network    import *
from desktop    import *
from resource   import *
from terminal   import *
from management import *
from diskpart   import *
from idv	import *


############
# 路由相关
############
app.add_url_rule('/',                        view_func=index)
app.add_url_rule('/setting',                 view_func=setting)
app.add_url_rule('/p2p',                     view_func=p2p)
app.add_url_rule('/management',              view_func=management)
app.add_url_rule('/desktop',                 view_func=desktop)
app.add_url_rule('/rdp',                     view_func=rdp)
app.add_url_rule('/spice',                   view_func=spice)


login.methods = ['POST']
app.add_url_rule('/login',                   view_func=login)

app.add_url_rule('/logout',                  view_func=logout)


############
# 权限相关
############
app.add_url_rule('/api/permit/check',        view_func=check_permit)

verify_permit.methods = ['POST']
app.add_url_rule('/api/permit/verify',       view_func=verify_permit)


############
# 资源相关
############
app.add_url_rule('/api/resource/list',       view_func=list_resources)

add_resource.methods = ['POST']
app.add_url_rule('/api/resource/add',        view_func=add_resource)

remove_resource.methods = ['POST']
app.add_url_rule('/api/resource/remove',     view_func=remove_resource)

clear_resources.methods = ['POST']
app.add_url_rule('/api/resource/clear',      view_func=clear_resources)

refresh_resources.methods = ['POST']
app.add_url_rule('/api/resource/refresh',    view_func=refresh_resources)

enable_resource.methods = ['POST']
app.add_url_rule('/api/resource/enable',     view_func=enable_resource)

disable_resource.methods = ['POST']
app.add_url_rule('/api/resource/disable',    view_func=disable_resource)


############
# 终端相关
############
wakeup.methods = ['POST']
app.add_url_rule('/api/wakeup',              view_func=wakeup)

shutdown.methods = ['POST']
app.add_url_rule('/api/shutdown',            view_func=shutdown)

reboot.methods = ['POST']
app.add_url_rule('/api/reboot',              view_func=reboot)

set_password.methods = ['POST']
app.add_url_rule('/api/password/set',        view_func=set_password)

app.add_url_rule('/api/time/get',            view_func=get_time)
set_time.methods = ['POST']
app.add_url_rule('/api/time/set',            view_func=set_time)

connect_test.methods = ['POST']
app.add_url_rule('/api/connect_test',        view_func=connect_test)

identify.methods = ['POST']
app.add_url_rule('/api/identify',            view_func=identify)

app.add_url_rule('/api/system/info',         view_func=system_info)

file_.methods = ['POST']
app.add_url_rule('/api/file',                view_func=file_)

connect_vncviewer.methods = ['POST']
app.add_url_rule('/api/vncviewer/connect',    view_func=connect_vncviewer)
disconnect_vncviewer.methods = ['POST']
app.add_url_rule('/api/vncviewer/disconnect', view_func=disconnect_vncviewer)

snapshot_screen.methods = ['POST']
app.add_url_rule('/api/screen/snapshot',      view_func=snapshot_screen)
lock_screen.methods = ['POST']
app.add_url_rule('/api/screen/lock',          view_func=lock_screen)
unlock_screen.methods = ['POST']
app.add_url_rule('/api/screen/unlock',        view_func=unlock_screen)

lock_input.methods = ['POST']
app.add_url_rule('/api/input/lock',           view_func=lock_input)
unlock_input.methods = ['POST']
app.add_url_rule('/api/input/unlock',         view_func=unlock_input)

push_camera.methods = ['POST']
app.add_url_rule('/api/camera/push',          view_func=push_camera)
stop_camera.methods = ['POST']
app.add_url_rule('/api/camera/stop',          view_func=stop_camera)

play_media.methods = ['POST']
app.add_url_rule('/api/media/play',           view_func=play_media)
stop_media.methods = ['POST']
app.add_url_rule('/api/media/stop',           view_func=stop_media)
pause_media.methods = ['POST']
app.add_url_rule('/api/media/pause',          view_func=pause_media)
resume_media.methods = ['POST']
app.add_url_rule('/api/media/resume',         view_func=resume_media)

start_record.methods = ['POST']
app.add_url_rule('/api/record/start',         view_func=start_record)
stop_record.methods = ['POST']
app.add_url_rule('/api/record/stop',          view_func=stop_record)

start_message.methods = ['POST']
app.add_url_rule('/api/message/start',        view_func=start_message)
stop_message.methods = ['POST']
app.add_url_rule('/api/message/stop',         view_func=stop_message)


app.add_url_rule('/api/network/get',          view_func=get_network)
#为了保持和云终端Windows版本的兼容性(aoqingy)
app.add_url_rule('/network/get',              view_func=get_network)
set_network.methods = ['POST']
app.add_url_rule('/api/network/set',          view_func=set_network)
#为了保持和云终端Windows版本的兼容性(aoqingy)
app.add_url_rule('/network/set',              view_func=set_network)
restart_network.methods = ['POST']
app.add_url_rule('/api/network/restart',      view_func=restart_network)

scan_wifi.methods = ['POST']
app.add_url_rule('/api/wifi/scan',               view_func=scan_wifi)
app.add_url_rule('/api/wifi/status',             view_func=status_wifi)
connect_wifi.methods = ['POST']
app.add_url_rule('/api/wifi/connect',            view_func=connect_wifi)
disconnect_wifi.methods = ['POST']
app.add_url_rule('/api/wifi/disconnect',         view_func=disconnect_wifi)

ping1.methods = ['POST']
app.add_url_rule('/api/network/ping1',           view_func=ping1)
ping2.methods = ['POST']
app.add_url_rule('/api/network/ping2',           view_func=ping2)

upgrade_via_network.methods = ['POST']
app.add_url_rule('/api/upgrade/network',         view_func=upgrade_via_network)
upgrade_via_usb.methods = ['POST']
app.add_url_rule('/api/upgrade/usb',             view_func=upgrade_via_usb)

license_via_network.methods = ['POST']
app.add_url_rule('/api/license/network',         view_func=license_via_network)
license_via_usb.methods = ['POST']
app.add_url_rule('/api/license/usb',             view_func=license_via_usb)

log_via_network.methods = ['POST']
app.add_url_rule('/api/log/network',             view_func=log_via_network)
log_via_usb.methods = ['POST']
app.add_url_rule('/api/log/usb',                 view_func=log_via_usb)

certificate_upload.methods = ['POST']
app.add_url_rule('/api/certificate/upload',      view_func=certificate_upload)

change_bootpng.methods = ['POST']
app.add_url_rule('/api/bootpng/change',          view_func=change_bootpng)
#为了保持和云终端Windows版本的兼容性(aoqingy)
app.add_url_rule('/bootpng/change',              view_func=change_bootpng)

change_lockjpg.methods = ['POST']
app.add_url_rule('/api/lockjpg/change',          view_func=change_lockjpg)
#为了保持和云终端Windows版本的兼容性(aoqingy)
app.add_url_rule('/lockjpg/change',              view_func=change_lockjpg)


################
# 终端管理相关
################
scan_terminals.methods = ['POST']
app.add_url_rule('/terminal/scan',             view_func=scan_terminals)

app.add_url_rule('/terminal/list',             view_func=list_terminals)

app.add_url_rule('/terminal/info',             view_func=get_terminal_info)

remove_terminals.methods = ['POST']
app.add_url_rule('/terminal/remove',           view_func=remove_terminals)

clear_terminals.methods = ['POST']
app.add_url_rule('/terminal/clear',            view_func=clear_terminals)

wakeup_terminals.methods = ['POST']
app.add_url_rule('/terminal/wakeup',           view_func=wakeup_terminals)

shutdown_terminals.methods = ['POST']
app.add_url_rule('/terminal/shutdown',         view_func=shutdown_terminals)

reboot_terminals.methods = ['POST']
app.add_url_rule('/terminal/reboot',           view_func=reboot_terminals)

app.add_url_rule('/terminal/uuids',            view_func=terminal_uuids)

app.add_url_rule('/terminal/time/get',         view_func=get_terminal_time)

set_terminal_time.methods = ['POST']
app.add_url_rule('/terminal/time/set',         view_func=set_terminal_time)

app.add_url_rule('/terminal/locate',           view_func=locate_terminals)

update_terminals.methods = ['POST']
app.add_url_rule('/terminal/update',           view_func=update_terminals)

upload_management.methods = ['POST']
app.add_url_rule('/management/upload',         view_func=upload_management)

remove_management.methods = ['POST']
app.add_url_rule('/management/remove',         view_func=remove_management)


##############
# 桌面接入相关
##############
get_desktops.methods = ['POST']
app.add_url_rule('/api/desktop/list',          view_func=get_desktops)

connect_virtualized_spice.methods = ['POST']
app.add_url_rule('/api/spice/connect',         view_func=connect_virtualized_spice)

connect_virtualized_rdp.methods = ['POST']
app.add_url_rule('/api/rdp/connect',           view_func=connect_virtualized_rdp)

connect_regular_rdp.methods = ['POST']
app.add_url_rule('/api/rdp/rconnect',          view_func=connect_regular_rdp)

connect_vmware.methods = ['POST']
app.add_url_rule('/api/vmware/connect',        view_func=connect_vmware)

connect_citrix.methods = ['POST']
app.add_url_rule('/api/citrix/connect',        view_func=connect_citrix)


##############
# 镜像管理相关
##############
app.add_url_rule('/file/list',                 view_func=list_files)
app.add_url_rule('/api/file/list',             view_func=list_files)

remove_files.methods = ['POST']
app.add_url_rule('/api/file/mremove',          view_func=remove_files)

rename_file.methods = ['POST']
app.add_url_rule('/api/file/rename',           view_func=rename_file)

app.add_url_rule('/api/file/status',           view_func=status_file)

stop_check_file.methods = ['POST']
app.add_url_rule('/api/file/check/stop',       view_func=stop_check_file)

copy_file.methods = ['POST']
app.add_url_rule('/api/file/copy/start',       view_func=copy_file)

download_file.methods = ['POST']
app.add_url_rule('/api/file/download/start',   view_func=download_file)

download_file_with_bt.methods = ['POST']
app.add_url_rule('/api/file/download/btstart', view_func=download_file_with_bt)

download_file_with_bt_by_curl.methods = ['POST']
app.add_url_rule('/api/file/download/bcstart', view_func=download_file_with_bt_by_curl)

mount_usb.methods = ['POST']
app.add_url_rule('/api/usb/mount',             view_func=mount_usb)

unmount_usb.methods = ['POST']
app.add_url_rule('/api/usb/unmount',           view_func=unmount_usb)


##############
# 分区管理相关
##############
#app.add_url_rule('/partition/list',             view_func=list_partitions)
#app.add_url_rule('/api/partition/list',         view_func=list_partitions)
#app.add_url_rule('/partition/info',             view_func=get_partition_info)
#app.add_url_rule('/api/partition/info',         view_func=get_partition_info)
#采用BT方式进行同传
#sync_partition.methods = ['POST']
#app.add_url_rule('/api/partition/sync/start',   view_func=sync_partition)
#app.add_url_rule('/partition/sync/torrent',     view_func=download_torrent)
#app.add_url_rule('/api/partition/sync/torrent', view_func=download_torrent)
#stop_sync_partition.methods = ['POST']
#app.add_url_rule('/api/partition/sync/stop',    view_func=stop_sync_partition)
#recv_partition.methods = ['POST']
#app.add_url_rule('/api/partition/receive',      view_func=recv_partition)
#采用DD方式通过NFS进行同传（准备删除）aoqingy
#nsync_partition.methods = ['POST']
#app.add_url_rule('/api/partition/nsync',        view_func=nsync_partition)
#nrecv_partition.methods = ['POST']
#app.add_url_rule('/api/partition/nreceive',     view_func=nrecv_partition)
#p2v_partition.methods = ['POST']
#app.add_url_rule('/api/partition/p2v',          view_func=p2v_partition)
#采用DD方式将云桌面下载到终端上（不建议批量操作）
#v2p_partition.methods = ['POST']
#app.add_url_rule('/api/partition/v2p',          view_func=v2p_partition)


##############
# PXE管理相关
##############
app.add_url_rule('/api/diskpart/cquery',       view_func=query_diskpart)

save_diskpart.methods = ['POST']
app.add_url_rule('/api/diskpart/csave',        view_func=save_diskpart)

restore_diskpart.methods = ['POST']
app.add_url_rule('/api/diskpart/crestore',     view_func=restore_diskpart)

mrestore_diskpart.methods = ['POST']
app.add_url_rule('/api/diskpart/cmrestore',    view_func=mrestore_diskpart)

mudpsend_diskpart.methods = ['POST']
app.add_url_rule('/api/diskpart/cmudpsend',    view_func=mudpsend_diskpart)

#update_winparam.methods = ['POST']
#app.add_url_rule('/api/winparam/update',        view_func=update_winparam)

upload_diskpart.methods = ['POST']
app.add_url_rule('/api/diskpart/upload',       view_func=upload_diskpart)

download_diskpart.methods = ['POST']
app.add_url_rule('/api/diskpart/download',     view_func=download_diskpart)


##############
# PXE管理相关
##############
app.add_url_rule('/api/idv/cpu',                view_func=get_cpu)
app.add_url_rule('/api/idv/memory',             view_func=get_memory)
app.add_url_rule('/api/idv/disk',               view_func=get_disks)
app.add_url_rule('/api/idv/iso',                view_func=get_isos)
app.add_url_rule('/api/idv/vfd',                view_func=get_vfds)
app.add_url_rule('/api/idv/pci',                view_func=get_pcis)
app.add_url_rule('/api/idv/adisk',              view_func=get_adisk)

create_disk.methods = ['POST']
app.add_url_rule('/api/idv/cdisk',              view_func=create_disk)

app.add_url_rule('/api/idv/list',               view_func=list_idvs)
app.add_url_rule('/api/idv/info',               view_func=get_idv_info)

create_idv.methods = ['POST']
app.add_url_rule('/api/idv/create',             view_func=create_idv)

remove_idv.methods = ['POST']
app.add_url_rule('/api/idv/remove',             view_func=remove_idv)

edit_idv_cpu.methods = ['POST']
app.add_url_rule('/api/idv/ecpu',               view_func=edit_idv_cpu)
edit_idv_memory.methods = ['POST']
app.add_url_rule('/api/idv/ememory',            view_func=edit_idv_memory)
edit_idv_cdrom.methods = ['POST']
app.add_url_rule('/api/idv/ecdrom',             view_func=edit_idv_cdrom)
edit_idv_floppy.methods = ['POST']
app.add_url_rule('/api/idv/efloppy',            view_func=edit_idv_floppy)
edit_idv_sdisk.methods = ['POST']
app.add_url_rule('/api/idv/esdisk',             view_func=edit_idv_sdisk)
edit_idv_ddisk.methods = ['POST']
app.add_url_rule('/api/idv/eddisk',             view_func=edit_idv_ddisk)
edit_idv_network.methods = ['POST']
app.add_url_rule('/api/idv/enetwork',           view_func=edit_idv_network)
edit_idv_pci.methods = ['POST']
app.add_url_rule('/api/idv/epci',               view_func=edit_idv_pci)
edit_idv_autostart.methods = ['POST']
app.add_url_rule('/api/idv/eautostart',         view_func=edit_idv_autostart)

app.add_url_rule('/api/idv/pdevice',            view_func=get_pci_devices)

connect_idv.methods = ['POST']
app.add_url_rule('/api/idv/connect',            view_func=connect_idv)


##############
# 引导切换相关
##############
app.add_url_rule('/api/terminal/bflist',       view_func=list_bcdfile)

upload_bcdfile.methods = ['POST']
app.add_url_rule('/api/terminal/bfupload',     view_func=upload_bcdfile)

app.add_url_rule('/api/terminal/blist',        view_func=list_bootloader)
#为了保持和云终端Windows版本的兼容性(aoqingy)
app.add_url_rule('/terminal/blist',            view_func=list_bootloader)

change_bootloader.methods = ['POST']
app.add_url_rule('/api/terminal/bchange',      view_func=change_bootloader)
#为了保持和云终端Windows版本的兼容性(aoqingy)
app.add_url_rule('/terminal/bchange',          view_func=change_bootloader)


##############
# USB重定向相关
##############
app.add_url_rule('/api/usbredir/status',        view_func=get_usbd_status)

start_usbd_service.methods = ['POST']
app.add_url_rule('/api/usbredir/start',         view_func=start_usbd_service)

stop_usbd_service.methods = ['POST']
app.add_url_rule('/api/usbredir/stop',          view_func=stop_usbd_service)

app.add_url_rule('/api/usbredir/port',          view_func=get_usbd_port)

app.add_url_rule('/api/usbredir/getcb',         view_func=get_usbd_callback)

create_usbd_callback.methods = ['POST']
app.add_url_rule('/api/usbredir/createcb',      view_func=create_usbd_callback)

close_usbd_callback.methods = ['POST']
app.add_url_rule('/api/usbredir/closecb',       view_func=close_usbd_callback)

app.add_url_rule('/api/usbredir/list',          view_func=list_usb_devices)

share_usb_device.methods = ['POST']
app.add_url_rule('/api/usbredir/share',         view_func=share_usb_device)

unshare_usb_device.methods = ['POST']
app.add_url_rule('/api/usbredir/unshare',       view_func=unshare_usb_device)


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=80, threaded=True)
    #app.run(host='0.0.0.0', port=80, threaded=True, debug=True)
