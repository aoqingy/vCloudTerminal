#!/bin/bash

#在杀死eog进程后，休眠2秒在刷新屏幕，避免图片不能消除的问题
#killall eog
pkill -9 eog
rm -rf /tmp/message.jpg
sleep 2
xrefresh
