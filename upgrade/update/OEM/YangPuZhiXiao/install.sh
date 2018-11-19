#!/bin/bash

cd `dirname $0`

cp -a logo/* ${SquashfsPath}/lib/plymouth/themes/ubuntu-logo/
cp -a logo/ubuntu_logo.png ${SquashfsPath}/lib/plymouth/

