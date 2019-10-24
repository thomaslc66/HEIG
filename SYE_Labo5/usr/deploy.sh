echo Deploying user application into the SD/MMC partition ...
cd ..
cd filesystem
./mount.sh
sudo cp ../usr/*.elf fs
./umount.sh
cd ../usr
