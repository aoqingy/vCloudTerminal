#!/bin/bash
cd `dirname $0`

echo
echo "Start to install logo ..."
echo

cp -a ./background/warty-final-ubuntu.png /usr/share/backgrounds/warty-final-ubuntu.png
cp -a ./icon/* /usr/share/ubiquity/pixmaps/
cp -a ./logo/* /usr/share/plymouth/themes/ubuntu-logo/
cp -a ./logo/ubuntu-logo.png /usr/share/plymouth/

#安装时轮转展示
cp -a ./picture/* /usr/share/ubiquity-slideshow/slides/screenshots/
cp -a ./html/* /usr/share/ubiquity-slideshow/slides/l10n/zh_CN/
cp -a ./html/* /usr/share/ubiquity-slideshow/slides/
cp -a ./index.html /usr/share/ubiquity-slideshow/slides/

echo "Finish logo installation."

