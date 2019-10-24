cmd_kernel/softirq.o := arm-linux-gnueabihf-gcc -Wp,-MD,kernel/.softirq.o.d  -Iinclude  -I.  -include include/generated/autoconf.h -D__KERNEL__ -D__SO3__ -Iinclude -fno-builtin -ffreestanding -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include -g -O0 -fno-common -marm -mno-thumb-interwork -march=armv7-a -Wall -Wstrict-prototypes -D__KERNEL__ -D__SO3__ -Iinclude -fno-builtin -ffreestanding -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include -I. -I./lib/libfdt  -Iarch/arm/include/ -Iarch/arm/vexpress/include/	  -c -o kernel/softirq.o kernel/softirq.c

source_kernel/softirq.o := kernel/softirq.c

deps_kernel/softirq.o := \
  include/bitops.h \
  include/types.h \
  arch/arm/include/asm/types.h \
  arch/arm/include/asm/cache.h \
  arch/arm/include/asm/processor.h \
  include/spinlock.h \
  arch/arm/include/asm/spinlock.h \
  arch/arm/include/asm/atomic.h \
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
  arch/arm/include/asm/atomic-generic.h \
  include/softirq.h \

kernel/softirq.o: $(deps_kernel/softirq.o)

$(deps_kernel/softirq.o):
