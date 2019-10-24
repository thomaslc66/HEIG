cmd_kernel/syscalls.o := arm-linux-gnueabihf-gcc -Wp,-MD,kernel/.syscalls.o.d  -Iinclude  -I.  -include include/generated/autoconf.h -D__KERNEL__ -D__SO3__ -Iinclude -fno-builtin -ffreestanding -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include -g -O0 -fno-common -marm -mno-thumb-interwork -march=armv7-a -Wall -Wstrict-prototypes -D__KERNEL__ -D__SO3__ -Iinclude -fno-builtin -ffreestanding -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include -I. -I./lib/libfdt  -Iarch/arm/include/ -Iarch/arm/vexpress/include/	  -c -o kernel/syscalls.o kernel/syscalls.c

source_kernel/syscalls.o := kernel/syscalls.c

deps_kernel/syscalls.o := \
    $(wildcard include/config/mmu.h) \
    $(wildcard include/config/ipc/pipe.h) \
    $(wildcard include/config/app/test/malloc.h) \
  arch/arm/include/asm/syscall.h \
  include/errno.h \
  include/types.h \
  arch/arm/include/asm/types.h \
  arch/arm/include/asm/cache.h \
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
  include/stddef.h \
  include/string.h \
  include/compiler.h \
  lib/libfdt/fdt.h \
  include/linker.h \
  include/process.h \
  include/list.h \
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
  include/vfs.h \
  include/stat.h \
  include/pipe.h \
  include/mutex.h \
  include/heap.h \
  include/sizes.h \

kernel/syscalls.o: $(deps_kernel/syscalls.o)

$(deps_kernel/syscalls.o):
