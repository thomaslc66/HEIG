cmd_kernel/main.o := arm-linux-gnueabihf-gcc -Wp,-MD,kernel/.main.o.d  -Iinclude  -I.  -include include/generated/autoconf.h -D__KERNEL__ -D__SO3__ -Iinclude -fno-builtin -ffreestanding -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include -g -O0 -fno-common -marm -mno-thumb-interwork -march=armv7-a -Wall -Wstrict-prototypes -D__KERNEL__ -D__SO3__ -Iinclude -fno-builtin -ffreestanding -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include -I. -I./lib/libfdt  -Iarch/arm/include/ -Iarch/arm/vexpress/include/	  -c -o kernel/main.o kernel/main.c

source_kernel/main.o := kernel/main.c

deps_kernel/main.o := \
    $(wildcard include/config/vexpress.h) \
    $(wildcard include/config/thread/env.h) \
    $(wildcard include/config/proc/env.h) \
  include/common.h \
  include/tinyprintf.h \
    $(wildcard include/config/debug/printk.h) \
  /usr/lib/gcc/x86_64-linux-gnu/5/include/stdarg.h \
  arch/arm/include/asm/types.h \
  include/fdt.h \
  include/memory.h \
    $(wildcard include/config/kernel/virt/addr.h) \
    $(wildcard include/config/ram/base.h) \
  include/types.h \
  arch/arm/include/asm/cache.h \
  arch/arm/include/asm/memory.h \
  lib/libfdt/libfdt.h \
  lib/libfdt/libfdt_env.h \
  include/stddef.h \
  include/string.h \
  include/compiler.h \
  lib/libfdt/fdt.h \
  include/linker.h \
  include/calibrate.h \
  include/calibrate.h \
  include/schedule.h \
  include/list.h \
  include/prefetch.h \
  arch/arm/include/asm/processor.h \
  include/thread.h \
  include/mmc.h \
    $(wildcard include/config/sys/mmc/max/blk/count.h) \
  include/part.h \
    $(wildcard include/config/sys/64bit/lba.h) \
    $(wildcard include/config/lba48.h) \
  include/driver.h \
  include/device.h \
  include/vfs.h \
  include/stat.h \
  include/process.h \
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
  arch/arm/include/asm/setup.h \
  arch/arm/include/asm/hardware/timer.h \
  arch/arm/include/asm/hardware/irq.h \
  arch/arm/include/asm/mmu.h \
    $(wildcard include/config/mmu.h) \
  include/apps/main_thread.h \

kernel/main.o: $(deps_kernel/main.o)

$(deps_kernel/main.o):
