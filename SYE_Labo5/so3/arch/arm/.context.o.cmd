cmd_arch/arm/context.o := arm-linux-gnueabihf-gcc -Wp,-MD,arch/arm/.context.o.d  -Iinclude  -I.  -include include/generated/autoconf.h -D__KERNEL__ -D__SO3__  -Iinclude -fno-builtin -ffreestanding -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include   -g -D__ASSEMBLY__       -I.  -Iarch/arm/include/ -Iarch/arm/vexpress/include/  -c -o arch/arm/context.o arch/arm/context.S

source_arch/arm/context.o := arch/arm/context.S

deps_arch/arm/context.o := \
    $(wildcard include/config/mmu.h) \
  arch/arm/include/asm/assembler.h \
  include/asm-offsets.h \
  include/generated/asm-offsets.h \
  arch/arm/include/asm/processor.h \
  arch/arm/include/asm/mmu.h \
  include/linkage.h \

arch/arm/context.o: $(deps_arch/arm/context.o)

$(deps_arch/arm/context.o):
