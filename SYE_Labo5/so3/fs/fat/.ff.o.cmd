cmd_fs/fat/ff.o := arm-linux-gnueabihf-gcc -Wp,-MD,fs/fat/.ff.o.d  -Iinclude  -I.  -include include/generated/autoconf.h -D__KERNEL__ -D__SO3__ -Iinclude -fno-builtin -ffreestanding -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include -g -O0 -fno-common -marm -mno-thumb-interwork -march=armv7-a -Wall -Wstrict-prototypes -D__KERNEL__ -D__SO3__ -Iinclude -fno-builtin -ffreestanding -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include -I. -I./lib/libfdt  -Iarch/arm/include/ -Iarch/arm/vexpress/include/	  -c -o fs/fat/ff.o fs/fat/ff.c

source_fs/fat/ff.o := fs/fat/ff.c

deps_fs/fat/ff.o := \
  include/fat/ff.h \
  include/fat/integer.h \
  include/fat/ffconf.h \
  include/fat/diskio.h \

fs/fat/ff.o: $(deps_fs/fat/ff.o)

$(deps_fs/fat/ff.o):
