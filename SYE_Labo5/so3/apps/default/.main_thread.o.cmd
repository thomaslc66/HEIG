cmd_apps/default/main_thread.o := arm-linux-gnueabihf-gcc -Wp,-MD,apps/default/.main_thread.o.d  -Iinclude  -I.  -include include/generated/autoconf.h -D__KERNEL__ -D__SO3__ -Iinclude -fno-builtin -ffreestanding -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include -g -O0 -fno-common -marm -mno-thumb-interwork -march=armv7-a -Wall -Wstrict-prototypes -D__KERNEL__ -D__SO3__ -Iinclude -fno-builtin -ffreestanding -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include -I. -I./lib/libfdt  -Iarch/arm/include/ -Iarch/arm/vexpress/include/	  -c -o apps/default/main_thread.o apps/default/main_thread.c

source_apps/default/main_thread.o := apps/default/main_thread.c

deps_apps/default/main_thread.o := \
  include/thread.h \
  arch/arm/include/asm/memory.h \
  include/types.h \
  arch/arm/include/asm/types.h \
  arch/arm/include/asm/cache.h \
  include/list.h \
  include/common.h \
  include/tinyprintf.h \
    $(wildcard include/config/debug/printk.h) \
  /usr/lib/gcc/x86_64-linux-gnu/5/include/stdarg.h \
  include/fdt.h \
  include/memory.h \
    $(wildcard include/config/kernel/virt/addr.h) \
    $(wildcard include/config/ram/base.h) \
  lib/libfdt/libfdt.h \
  lib/libfdt/libfdt_env.h \
  include/stddef.h \
  include/string.h \
  include/compiler.h \
  lib/libfdt/fdt.h \
  include/linker.h \
  include/prefetch.h \
  arch/arm/include/asm/processor.h \
  include/schedule.h \
  include/mutex.h \
  arch/arm/include/asm/atomic.h \
  arch/arm/include/asm/atomic-generic.h \
  include/spinlock.h \
  arch/arm/include/asm/spinlock.h \
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
  arch/arm/include/asm/hardware/timer.h \

apps/default/main_thread.o: $(deps_apps/default/main_thread.o)

$(deps_apps/default/main_thread.o):
