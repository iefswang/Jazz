#/bin/bash
#Program:
# test RJ45 whether it is good or bad
#History: 
# 2011/07/24 wfs first realease
echo "RJ45 port test"
upload=1
download=1
#if [ $# != 2 ];
#then 
#echo "sh net.sh localhost_ip server_ip"
#echo "for example:"
#echo "sh net.sh 219.219.218.111 219.219.218.122"
#echo "the parameter is two, please try again" && exit 1


#fi
ifconfig eth0 219.219.218.112
ifconfig eth0 down
ifconfig eth0 up
ping -c 3 219.219.218.1
#mount -o nolock -o tcp 219.219.218.209:/var/nfs /mnt
#echo "nfs is ready..."

#mv /test233/net/testfile /mnt/test233/net/ && echo "upload file succed..." && upload=0 ||  echo "upload file fail..."
#mv /mnt/test233/net/testfile /test233/net && echo "download file succed..." && download=0 ||  echo "download file fail..."

#if [ $upload -eq  0 -o $download -eq 0 ];
#then
#	echo "RJ25 port is OK"
#else
#	echo "RJ45 port has a problem"
#fi
