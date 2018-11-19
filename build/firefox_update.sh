#!/bin/bash

#$1: filename (/root/.mozilla/firefox/*.default/prefs.js)
#$2: key (browser.startup.homepage)
#$3: value (www.baidu.com)
#$4: type (bool, int, string)
#Examples:
#/root/.mozilla/firefox/*.default/prefs.js browser.startup.homepage localhost string
#/root/.mozilla/firefox/*.default/prefs.js browser.tabs.closeWindowWithLastTab false bool
echo "FILE : $1"
echo "KEY  : $2"
echo "VALUE: $3"
echo "TYPE : $4"
echo

if [[ "$4" == "string" ]]
then
    PREFIX='"'
else
    PREFIX=
fi
echo '"'"$2"'"'
echo "$PREFIX$3$PREFIX"
echo

if grep '"'"$2"'"' $1
then
    echo 'Replacing:'
    echo 's/^user_pref("'"$2"'", .*/user_pref("'"$2"'", '"$PREFIX$3$PREFIX"');/g'
    sed -i -e 's/^user_pref("'"$2"'", .*/user_pref("'"$2"'", '"$PREFIX$3$PREFIX"');/g' $1
else
    echo 'Inserting:'
    echo 'user_pref("'"$2"'", '"$PREFIX$3$PREFIX"');'
    echo 'user_pref("'"$2"'", '"$PREFIX$3$PREFIX"');' >> $1
fi
echo
echo
