#boot_config.sh
#/bin/bash

DIR="/home/swhite/Smart-Patrol"

$DIR/configure


wvdial --config=$DIR/wvdial.config &

#sleep 10

#STRING=`ping -c 3 baidu.com | grep 64 | awk '{print $1}'`

#if [$STRING -eq 0]
#	then
#	wvdial --config=$DIR/wvdial.config > $DIR/wvdial.log

#fi


