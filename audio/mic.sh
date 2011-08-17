#!/bin/bash
#Program:
#	test mic
#History:
#	2011/07/25	wfs	first release
echo "mic test"
if [ $# != 1  ];
then
echo "sh mic.sh [record_filename]"
echo "for example: sh mic.sh record.wav"
echo "parameters are only one,please check again"
exit 1
fi
# make devices inodes
if [ ! -d /dev/snd  ];
then
mkdir /dev/snd
mknod /dev/snd/controlC0 c 116 0
mknod /dev/snd/hwC0D0 c 116 4
mknod /dev/snd/pcmC0D0c c 116 24
mknod /dev/snd/pcmC0D0p c 116 16
mknod /dev/snd/seq c 116 1
mknod /dev/snd/timer c 116 33
amixer -q -c 0 sset 'Speaker',0  unmute
fi	
arecord  -d 10 -f cd $1
if [ $? == 0 ];
then
echo "microphone test is over" 
else
echo "microphone test failed"
fi
