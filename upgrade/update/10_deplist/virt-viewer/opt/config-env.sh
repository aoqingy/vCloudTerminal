#!/bin/bash

export INSTALL_PATH=/opt/
export BIN_PATH=/opt/bin
export PKG_CONFIG_PATH=$INSTALL_PATH/lib/pkgconfig:$INSTALL_PATH/share/pkgconfig
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$INSTALL_PATH/lib
export PATH=/opt/bin:$PATH
#export PKG_CONFIG_PATH=${INSTALL_PATH}/lib/pkgconfig:${INSTALL_PATH}/share/pkgconfig
