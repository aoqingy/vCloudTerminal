#!/bin/bash
cd `dirname $0`

OEM=''    #The codes are just for reference and not used (aoqingy)

echo
echo "Start to install OEM ..."
echo

if [[ ${OEM} != '' ]]
then
  [[ -d ./${OEM} ]] && {
    ./${OEM}/install.sh
  }
fi

echo "Finish OEM installation."

