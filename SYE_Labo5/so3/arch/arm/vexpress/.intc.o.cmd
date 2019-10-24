cmd_arch/arm/vexpress/intc.o := arm-linux-gnueabihf-gcc -Wp,-MD,arch/arm/vexpress/.intc.o.d  -Iinclude  -I.  -include include/generated/autoconf.h -D__KERNEL__ -D__SO3__ -Iinclude -fno-builtin -ffreestanding -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include -g -O0 -fno-common -marm -mno-thumb-interwork -march=armv7-a -Wall -Wstrict-prototypes -D__KERNEL__ -D__SO3__ -Iinclude -fno-builtin -ffreestanding -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include -I. -I./lib/libfdt  -Iarch/arm/include/ -Iarch/arm/vexpress/include/	  -c -o arch/arm/vexpress/intc.o arch/arm/vexpress/intc.c

source_arch/arm/vexpress/intc.o := arch/arm/vexpress/intc.c

deps_arch/arm/vexpress/intc.o := \
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
  include/device.h \
  include/driver.h \
  arch/arm/include/asm/hardware/irq.h \
  arch/arm/include/asm/io.h \
  arch/arm/vexpress/include/mach/intc.h \

arch/arm/vexpress/intc.o: $(deps_arch/arm/vexpress/intc.o)

$(deps_arch/arm/vexpress/intc.o):
