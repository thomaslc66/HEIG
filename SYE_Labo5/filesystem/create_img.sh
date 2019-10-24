#!/bin/bash

if [ $# -ne 1 ]; then
	echo "Please provide the name of the flash image"
	exit 0
fi 

#create image first
dd if=/dev/zero of=$1 bs=4096 count=4096
DEVLOOP=$(sudo losetup --partscan --find --show $1)

#create the partition this way
(echo o; echo n; echo p; echo; echo; echo; echo; echo; echo t; echo; echo c; echo w) | sudo fdisk $DEVLOOP;

sudo mkfs.vfat ${DEVLOOP}p1
sudo losetup -d $DEVLOOP
