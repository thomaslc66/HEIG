F_DEVLOOP=./.devloop
DEVLOOP=$(cat $F_DEVLOOP)

sudo umount fs


if [ ! -f $F_DEVLOOP ]; then
	echo "Nothing mounted"
	exit 1
fi


sudo losetup -d $DEVLOOP
exit 0


