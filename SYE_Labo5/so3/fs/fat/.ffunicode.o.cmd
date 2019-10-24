cmd_fs/fat/ffunicode.o := arm-linux-gnueabihf-gcc -Wp,-MD,fs/fat/.ffunicode.o.d  -Iinclude  -I.  -include include/generated/autoconf.h -D__KERNEL__ -D__SO3__ -Iinclude -fno-builtin -ffreestanding -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include -g -O0 -fno-common -marm -mno-thumb-interwork -march=armv7-a -Wall -Wstrict-prototypes -D__KERNEL__ -D__SO3__ -Iinclude -fno-builtin -ffreestanding -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include -I. -I./lib/libfdt  -Iarch/arm/include/ -Iarch/arm/vexpress/include/	  -c -o fs/fat/ffunicode.o fs/fat/ffunicode.c

source_fs/fat/ffunicode.o := fs/fat/ffunicode.c

deps_fs/fat/ffunicode.o := \
  include/fat/ff.h \
  include/fat/integer.h \
  include/fat/ffconf.h \

fs/fat/ffunicode.o: $(deps_fs/fat/ffunicode.o)

$(deps_fs/fat/ffunicode.o):
