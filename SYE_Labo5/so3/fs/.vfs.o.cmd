cmd_fs/vfs.o := arm-linux-gnueabihf-gcc -Wp,-MD,fs/.vfs.o.d  -Iinclude  -I.  -include include/generated/autoconf.h -D__KERNEL__ -D__SO3__ -Iinclude -fno-builtin -ffreestanding -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include -g -O0 -fno-common -marm -mno-thumb-interwork -march=armv7-a -Wall -Wstrict-prototypes -D__KERNEL__ -D__SO3__ -Iinclude -fno-builtin -ffreestanding -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include -I. -I./lib/libfdt  -Iarch/arm/include/ -Iarch/arm/vexpress/include/	  -c -o fs/vfs.o fs/vfs.c

source_fs/vfs.o := fs/vfs.c

deps_fs/vfs.o := \
    $(wildcard include/config/proc/env.h) \
    $(wildcard include/config/fs/fat.h) \
  include/vfs.h \
  include/types.h \
  arch/arm/include/asm/types.h \
  arch/arm/include/asm/cache.h \
  include/stat.h \
  include/stddef.h \
  include/process.h \
  include/list.h \
  include/common.h \
  include/tinyprintf.h \
    $(wildcard include/config/debug/printk.h) \
  /usr/lib/gcc/x86_64-linux-gnu/5/include/stdarg.h \
  include/fdt.h \
  include/memory.h \
    $(wildcard include/config/kernel/virt/addr.h) \
    $(wildcard include/config/ram/base.h) \
  arch/arm/include/asm/memory.h \
  lib/libfdt/libfdt.h \
  lib/libfdt/libfdt_env.h \
  include/string.h \
  include/compiler.h \
  lib/libfdt/fdt.h \
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
  include/heap.h \
  include/sizes.h \
  include/errno.h \
  arch/arm/include/asm/hardware/serial.h \
  include/mutex.h \
  include/fat/fat.h \

fs/vfs.o: $(deps_fs/vfs.o)

$(deps_fs/vfs.o):
