cmd_arch/arm/mmu.o := arm-linux-gnueabihf-gcc -Wp,-MD,arch/arm/.mmu.o.d  -Iinclude  -I.  -include include/generated/autoconf.h -D__KERNEL__ -D__SO3__ -Iinclude -fno-builtin -ffreestanding -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include -g -O0 -fno-common -marm -mno-thumb-interwork -march=armv7-a -Wall -Wstrict-prototypes -D__KERNEL__ -D__SO3__ -Iinclude -fno-builtin -ffreestanding -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include -I. -I./lib/libfdt  -Iarch/arm/include/ -Iarch/arm/vexpress/include/	  -c -o arch/arm/mmu.o arch/arm/mmu.c

source_arch/arm/mmu.o := arch/arm/mmu.c

deps_arch/arm/mmu.o := \
    $(wildcard include/config/ram/base.h) \
    $(wildcard include/config/kernel/virt/addr.h) \
  include/memory.h \
  include/types.h \
  arch/arm/include/asm/types.h \
  arch/arm/include/asm/cache.h \
  arch/arm/include/asm/memory.h \
  include/heap.h \
  include/stddef.h \
  include/sizes.h \
  include/fdt.h \
  lib/libfdt/libfdt.h \
  lib/libfdt/libfdt_env.h \
  include/string.h \
  include/compiler.h \
  lib/libfdt/fdt.h \
  arch/arm/include/asm/mmu.h \
    $(wildcard include/config/mmu.h) \
  include/process.h \
  include/list.h \
  include/common.h \
  include/tinyprintf.h \
    $(wildcard include/config/debug/printk.h) \
  /usr/lib/gcc/x86_64-linux-gnu/5/include/stdarg.h \
  include/linker.h \
  include/prefetch.h \
  arch/arm/include/asm/processor.h \
  include/thread.h \
  include/schedule.h \
  include/elf-struct.h \
  arch/arm/include/asm/byteorder.h \
  include/byteorder/little_endian.h \
  include/byteorder/swab.h \
  include/byteorder/generic.h \
  include/elf-em.h \
  include/sync.h \
  include/spinlock.h \
  arch/arm/include/asm/spinlock.h \
  arch/arm/include/asm/atomic.h \
  arch/arm/include/asm/atomic-generic.h \
  arch/arm/include/asm/cacheflush.h \
  arch/arm/vexpress/include/mach/uart.h \

arch/arm/mmu.o: $(deps_arch/arm/mmu.o)

$(deps_arch/arm/mmu.o):
