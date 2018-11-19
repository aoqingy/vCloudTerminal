#!/bin/bash
kill -9 `ps -ef|awk '$0 ~ /ffplay/ && $0 !~ /awk/''{print $2}'`
