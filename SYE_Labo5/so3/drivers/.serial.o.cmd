cmd_drivers/serial.o := arm-linux-gnueabihf-gcc -Wp,-MD,drivers/.serial.o.d  -Iinclude  -I.  -include include/generated/autoconf.h -D__KERNEL__ -D__SO3__ -Iinclude -fno-builtin -ffreestanding -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include -g -O0 -fno-common -marm -mno-thumb-interwork -march=armv7-a -Wall -Wstrict-prototypes -D__KERNEL__ -D__SO3__ -Iinclude -fno-builtin -ffreestanding -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include -I. -I./lib/libfdt  -Iarch/arm/include/ -Iarch/arm/vexpress/include/	  -c -o drivers/serial.o drivers/serial.c

source_drivers/serial.o := drivers/serial.c

deps_drivers/serial.o := \
    $(wildcard include/config/vexpress.h) \
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
  arch/arm/include/asm/hardware/serial.h \
  arch/arm/include/asm/processor.h \
  include/mutex.h \
  include/list.h \
  include/prefetch.h \
  arch/arm/include/asm/atomic.h \
  arch/arm/include/asm/atomic-generic.h \
  include/spinlock.h \
  arch/arm/include/asm/spinlock.h \
  include/thread.h \
  include/schedule.h \
  arch/arm/vexpress/include/mach/uart.h \

drivers/serial.o: $(deps_drivers/serial.o)

$(deps_drivers/serial.o):
