#!/bin/bash

dpkg -i /home/vClassTerminal/upgrade/update/deplist/deb/ica*.deb
touch /tmp/empty.ica
firefox file:///tmp/empty.ica

