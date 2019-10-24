cmd_arch/arm/cacheflush.o := arm-linux-gnueabihf-gcc -Wp,-MD,arch/arm/.cacheflush.o.d  -Iinclude  -I.  -include include/generated/autoconf.h -D__KERNEL__ -D__SO3__  -Iinclude -fno-builtin -ffreestanding -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include   -g -D__ASSEMBLY__       -I.  -Iarch/arm/include/ -Iarch/arm/vexpress/include/  -c -o arch/arm/cacheflush.o arch/arm/cacheflush.S

source_arch/arm/cacheflush.o := arch/arm/cacheflush.S

deps_arch/arm/cacheflush.o := \
  include/linkage.h \

arch/arm/cacheflush.o: $(deps_arch/arm/cacheflush.o)

$(deps_arch/arm/cacheflush.o):
