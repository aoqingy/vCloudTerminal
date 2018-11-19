#!/bin/bash
cd `dirname $0`
. ./vf_display.sh

pulseaudio -D

get_usb()
{
    usb_label=''
    usb=(`mount |awk '/media\/root/{print $3}'`)
    [[ ${#usb[@]} == 0 ]] && echo 'no usb' || {
        for list in ${usb[@]}
        do
            usb_label=${usb_label}\ ${list##*\/}
        done
        usb_label=(${usb_label[@]})

        for ((i=0;i<${#usb[@]};i++))
        do
            usb_opt=${usb_opt}\ \/drive:"${usb_label[$i]}",${usb[$i]}
        done
    }
}
#get_usb

# by freerdp-x11 1.1.0
#xfreerdp /u:$3 /p:$4 /f /bpp:16 /sound:sys:alsa /microphone:sys:alsa /rfx /rfx-mode:video /cert-ignore /multimedia /fonts -encryption -window-drag -nego -sec-rdp /gdi:hw /drive:"Removable Device",/media/root --plugin drdynvc --data tsmf:decoder:gstreamer /v:$1:$2

# by freerdp2-x11 2.0.0
xfreerdp /u:$3 /p:$4 /f /bpp:16 /sound:sys:pulse /microphone:sys:pulse /multimedia:sys:pulse /cert-ignore /gdi:hw /rfx -decorations -encryption -window-drag -compression +async-input +async-transport +multitransport +fonts -jpeg -bitmap-cache -offscreen-cache -glyph-cache /drive:"Removable Device",/media/root /v:$1:$2
