#!/bin/bash
#Program:
#	test wifi
#History:
#	2011/07/27	wfs	first release
WIRELESS_TOOLS=/wireless_tools.29/
echo "wifi test"
if [ $# != 1 ];
then
	echo "sh wifi.sh [web_device_inode]"
	echo "the parameter is only one,please check again."
	exit 1
fi
ifconfig $1 up
#$WIRELESS_TOOLS/iwlist $1 scan 
/wireless_tools.29/iwlist $1 scan
if [ $? -gt 0 ];
then
	echo "wifi module is innormal,please check it"
	exit 1
fi
$WIRELESS_TOOLS/iwconfig $1 essid "Embedded System Lab AP"
$WIRELESS_TOOLS/iwconfig $1 
if [ $? == 0 ];
then
	echo "wifi configures well" 
else
	echo "wifi configure failed"
	exit 1
fi
echo "enter wifi ip(AP router is 219.219.218.1):"
read  WIFI_IP
ifconfig $1 $WIFI_IP
ifconfig $1 down
ifconfig $1 up
ping -c 3 219.219.218.1 && echo "WLAN is ready" || echo "WLAN is not ready"
