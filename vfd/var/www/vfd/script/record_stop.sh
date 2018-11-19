#!/bin/bash
kill -2 `ps -ef|awk '$0 ~ /recordmydesktop/ && $0 !~ /awk/''{print $2}'`

#ffmpeg -i /home/screenrecord.ogv -acodec libmp3lame -acodec ac3 -ab 128k -ac 2 -vcodec libx264 -preset slow -crf 22 -threads 4 /home/screenrecord.mp4
#rm -rf /home/screenrecord.ogv

