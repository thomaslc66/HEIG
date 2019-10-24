cmd_arch/arm/boot/head.o := arm-linux-gnueabihf-gcc -Wp,-MD,arch/arm/boot/.head.o.d  -Iinclude  -I.  -include include/generated/autoconf.h -D__KERNEL__ -D__SO3__  -Iinclude -fno-builtin -ffreestanding -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include   -g -D__ASSEMBLY__        -I.  -Iarch/arm/include/ -Iarch/arm/vexpress/include/  -c -o arch/arm/boot/head.o arch/arm/boot/head.S

source_arch/arm/boot/head.o := arch/arm/boot/head.S

deps_arch/arm/boot/head.o := \
    $(wildcard include/config/mmu.h) \
    $(wildcard include/config/ram/base.h) \
  include/linkage.h \
  arch/arm/include/asm/processor.h \
  arch/arm/include/asm/mmu.h \
  arch/arm/include/asm/memory.h \
  include/thread.h \

arch/arm/boot/head.o: $(deps_arch/arm/boot/head.o)

$(deps_arch/arm/boot/head.o):
