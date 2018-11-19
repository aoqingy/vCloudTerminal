#!/bin/bash

test_domain=${1}
test_domain=${test_domain#*//}
test_domain=${test_domain%%/*}
test_domain=${test_domain%%:*}

#STATUS_CODE=`curl -o /dev/null --connect-timeout 3 -s -w %{http_code} ${test_domain}`
#if [[ "$STATUS_CODE" == 200 ]]
#then
#	exit 0
#else
#	exit 1
#fi
if [[ $1 =~ ^http ]]
then
    wget --no-check-certificate ${1} -O /tmp/tmpfile -T 3
else
    ping ${test_domain} -c 1 &> /dev/null
fi

