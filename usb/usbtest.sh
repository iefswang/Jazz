#!/bin/bash
#Program:
# test usb interface fuction
#History:
# 2011/07/13 wfs first release
echo "usb test"
if [ ! -e /dev/sda1 ];
then
	mknod /dev/sda1
fi
mount /dev/sda1 /mnt 
if [ $? == 0 ];
then
	echo "test reading... ..." 
else
	echo "can not mount usb flash" 
	exit 1
fi
mv  ./testfile /mnt/
if [ -e /mnt/testfile ];
then
echo "usb write succed!"
else
echo "usb write test fail!"
fi
mv  /mnt/testfile .
if [ -e ./testfile ];
then
echo "usb read succed!"
umount /mnt
else
echo "usb read fail!"
fi
exit 0
