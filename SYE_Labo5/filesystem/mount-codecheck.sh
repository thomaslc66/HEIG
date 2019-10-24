#!/bin/bash
FS_IMG=flash
SCRIPT_IMG=./create_img-codecheck.sh

if [ ! -f $FS_IMG ]; then
	echo "Creating image"sh  $FS_IMG
	bash $SCRIPT_IMG $FS_IMG

	if [ $? -ne 0 ]; then
		echo "Error while creating image"
		exit 1
	fi
	sleep 1
fi

DEVLOOP=$(sudo losetup --find --show $FS_IMG)
mkdir -p fs
sudo mount "$DEVLOOP" fs -o umask=002,uid=$USER,gid=$USER

echo $DEVLOOP > .devloop

exit 0
