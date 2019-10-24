cmd_arch/arm/exception.o := arm-linux-gnueabihf-gcc -Wp,-MD,arch/arm/.exception.o.d  -Iinclude  -I.  -include include/generated/autoconf.h -D__KERNEL__ -D__SO3__  -Iinclude -fno-builtin -ffreestanding -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include   -g -D__ASSEMBLY__       -I.  -Iarch/arm/include/ -Iarch/arm/vexpress/include/  -c -o arch/arm/exception.o arch/arm/exception.S

source_arch/arm/exception.o := arch/arm/exception.S

deps_arch/arm/exception.o := \
  arch/arm/include/asm/processor.h \

arch/arm/exception.o: $(deps_arch/arm/exception.o)

$(deps_arch/arm/exception.o):
