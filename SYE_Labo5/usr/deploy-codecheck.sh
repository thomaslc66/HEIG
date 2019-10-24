echo Deploying user application into the SD/MMC partition ...
cd ..
cd filesystem
./mount-codecheck.sh
sudo cp ../usr/*.elf fs
./umount-codecheck.sh
cd ../usr
