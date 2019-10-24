cmd_kernel/eabi_compat.o := arm-linux-gnueabihf-gcc -Wp,-MD,kernel/.eabi_compat.o.d  -Iinclude  -I.  -include include/generated/autoconf.h -D__KERNEL__ -D__SO3__ -Iinclude -fno-builtin -ffreestanding -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include -g -O0 -fno-common -marm -mno-thumb-interwork -march=armv7-a -Wall -Wstrict-prototypes -D__KERNEL__ -D__SO3__ -Iinclude -fno-builtin -ffreestanding -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include -I. -I./lib/libfdt  -Iarch/arm/include/ -Iarch/arm/vexpress/include/	  -c -o kernel/eabi_compat.o kernel/eabi_compat.c

source_kernel/eabi_compat.o := kernel/eabi_compat.c

deps_kernel/eabi_compat.o := \

kernel/eabi_compat.o: $(deps_kernel/eabi_compat.o)

$(deps_kernel/eabi_compat.o):
