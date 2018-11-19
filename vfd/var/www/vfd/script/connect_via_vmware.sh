#!/bin/bash
cd `dirname $0`
. ./vf_display.sh

vmware-view --fullscreen --serverURL="$1" --userName=$2 --password=$3 --nonInteractive
