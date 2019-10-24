cmd_lib/findbit.o := arm-linux-gnueabihf-gcc -Wp,-MD,lib/.findbit.o.d  -Iinclude  -I.  -include include/generated/autoconf.h -D__KERNEL__ -D__SO3__  -Iinclude -fno-builtin -ffreestanding -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include   -g -D__ASSEMBLY__       -I.  -Iarch/arm/include/ -Iarch/arm/vexpress/include/  -c -o lib/findbit.o lib/findbit.S

source_lib/findbit.o := lib/findbit.S

deps_lib/findbit.o := \

lib/findbit.o: $(deps_lib/findbit.o)

$(deps_lib/findbit.o):
