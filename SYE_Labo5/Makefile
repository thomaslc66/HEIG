
.PHONY: all so3 libc usr clean

all: so3 libc usr
	echo "Compilation done"

so3:
	cd so3/ && make

libc:
	cd usr/libc/ && make

usr:
	cd usr/ && make && ./deploy.sh


clean:
	cd so3/ && make clean
	cd usr/libc/ && make clean
	cd usr/ && make clean
