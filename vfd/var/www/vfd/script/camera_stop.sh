#!/bin/bash
kill -9 `ps -ef|awk '$0 ~ /ffmpeg -i/ && $0 !~ /awk/''{print $2}'`
