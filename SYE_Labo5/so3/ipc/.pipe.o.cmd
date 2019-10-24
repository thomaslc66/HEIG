cmd_ipc/pipe.o := arm-linux-gnueabihf-gcc -Wp,-MD,ipc/.pipe.o.d  -Iinclude  -I.  -include include/generated/autoconf.h -D__KERNEL__ -D__SO3__ -Iinclude -fno-builtin -ffreestanding -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include -g -O0 -fno-common -marm -mno-thumb-interwork -march=armv7-a -Wall -Wstrict-prototypes -D__KERNEL__ -D__SO3__ -Iinclude -fno-builtin -ffreestanding -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include -I. -I./lib/libfdt  -Iarch/arm/include/ -Iarch/arm/vexpress/include/	  -c -o ipc/pipe.o ipc/pipe.c

source_ipc/pipe.o := ipc/pipe.c

deps_ipc/pipe.o := \
  include/errno.h \
  include/types.h \
  arch/arm/include/asm/types.h \
  arch/arm/include/asm/cache.h \
  include/heap.h \
  include/stddef.h \
  include/sizes.h \
  include/limits.h \
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
  include/pipe.h \
  include/mutex.h \
  arch/arm/include/asm/atomic.h \
  arch/arm/include/asm/atomic-generic.h \
  include/spinlock.h \
  arch/arm/include/asm/spinlock.h \
  include/thread.h \
  include/schedule.h \
  include/sync.h \
  include/vfs.h \
  include/stat.h \

ipc/pipe.o: $(deps_ipc/pipe.o)

$(deps_ipc/pipe.o):
