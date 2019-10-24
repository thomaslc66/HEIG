cmd_lib/div64.o := arm-linux-gnueabihf-gcc -Wp,-MD,lib/.div64.o.d  -Iinclude  -I.  -include include/generated/autoconf.h -D__KERNEL__ -D__SO3__ -Iinclude -fno-builtin -ffreestanding -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include -g -O0 -fno-common -marm -mno-thumb-interwork -march=armv7-a -Wall -Wstrict-prototypes -D__KERNEL__ -D__SO3__ -Iinclude -fno-builtin -ffreestanding -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include -I. -I./lib/libfdt  -Iarch/arm/include/ -Iarch/arm/vexpress/include/	  -c -o lib/div64.o lib/div64.c

source_lib/div64.o := lib/div64.c

deps_lib/div64.o := \
  include/types.h \
  arch/arm/include/asm/types.h \
  arch/arm/include/asm/cache.h \

lib/div64.o: $(deps_lib/div64.o)

$(deps_lib/div64.o):
