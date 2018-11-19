#!/bin/bash
cd `dirname $0`

echo
echo "Start to install tools ..."
echo

#下面是做什么用途的？(aoqingy)
cp -a ./bin/* /usr/bin/
#cp -a ./remote-viewer.desktop /usr/share/applications/

echo "Finish tools installation."

