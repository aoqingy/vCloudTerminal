#!/bin/bash

[[ -d /usr/lib/mozilla ]] && {
	cp -a ./iceweasel/npSpiceConsole.so /usr/lib/mozilla/plugins/
}

[[ -d /usr/lib/firefox ]] && {
	cp -a ./firefox/npSpiceConsole.so /usr/lib/firefox/browser/plugins/
}

mkdir -p /usr/libexec/
cat > /usr/libexec/spice-xpi-client-remote-viewer <<EOF
#!/bin/sh
logger -t spice "starting remote-viewer --spice-controller \$@..."
env | logger -t spice
exec remote-viewer -k --spice-controller "\$@" 2>&1 | logger -t spice
logger -t spice "remote-viewer execution failed"
EOF
chmod +x /usr/libexec/spice-xpi-client-remote-viewer
ln -sf /usr/libexec/spice-xpi-client-remote-viewer /etc/alternatives/spice-xpi-client
ln -sf /etc/alternatives/spice-xpi-client /usr/libexec/spice-xpi-client
