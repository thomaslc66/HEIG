cmd_lib/string.o := arm-linux-gnueabihf-gcc -Wp,-MD,lib/.string.o.d  -Iinclude  -I.  -include include/generated/autoconf.h -D__KERNEL__ -D__SO3__ -Iinclude -fno-builtin -ffreestanding -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include -g -O0 -fno-common -marm -mno-thumb-interwork -march=armv7-a -Wall -Wstrict-prototypes -D__KERNEL__ -D__SO3__ -Iinclude -fno-builtin -ffreestanding -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include -I. -I./lib/libfdt  -Iarch/arm/include/ -Iarch/arm/vexpress/include/	  -c -o lib/string.o lib/string.c

source_lib/string.o := lib/string.c

deps_lib/string.o := \
  include/stddef.h \
  include/ctype.h \

lib/string.o: $(deps_lib/string.o)

$(deps_lib/string.o):
