cmd_arch/arm/setup.o := arm-linux-gnueabihf-gcc -Wp,-MD,arch/arm/.setup.o.d  -Iinclude  -I.  -include include/generated/autoconf.h -D__KERNEL__ -D__SO3__ -Iinclude -fno-builtin -ffreestanding -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include -g -O0 -fno-common -marm -mno-thumb-interwork -march=armv7-a -Wall -Wstrict-prototypes -D__KERNEL__ -D__SO3__ -Iinclude -fno-builtin -ffreestanding -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include -I. -I./lib/libfdt  -Iarch/arm/include/ -Iarch/arm/vexpress/include/	  -c -o arch/arm/setup.o arch/arm/setup.c

source_arch/arm/setup.o := arch/arm/setup.c

deps_arch/arm/setup.o := \
    $(wildcard include/config/mmu.h) \
    $(wildcard include/config/ram/base.h) \
  include/tinyprintf.h \
    $(wildcard include/config/debug/printk.h) \
  /usr/lib/gcc/x86_64-linux-gnu/5/include/stdarg.h \
  arch/arm/include/asm/types.h \
  include/memory.h \
    $(wildcard include/config/kernel/virt/addr.h) \
  include/types.h \
  arch/arm/include/asm/cache.h \
  arch/arm/include/asm/memory.h \
  include/driver.h \
  include/linker.h \
  include/device.h \
  include/fdt.h \
  lib/libfdt/libfdt.h \
  lib/libfdt/libfdt_env.h \
  include/stddef.h \
  include/string.h \
  include/compiler.h \
  lib/libfdt/fdt.h \
  arch/arm/include/asm/processor.h \
  arch/arm/include/asm/setup.h \
  arch/arm/include/asm/hardware/irq.h \
  include/common.h \
  arch/arm/include/asm/mmu.h \
  include/process.h \
  include/list.h \
  include/prefetch.h \
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

arch/arm/setup.o: $(deps_arch/arm/setup.o)

$(deps_arch/arm/setup.o):
