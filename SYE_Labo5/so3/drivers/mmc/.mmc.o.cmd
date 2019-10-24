cmd_drivers/mmc/mmc.o := arm-linux-gnueabihf-gcc -Wp,-MD,drivers/mmc/.mmc.o.d  -Iinclude  -I.  -include include/generated/autoconf.h -D__KERNEL__ -D__SO3__ -Iinclude -fno-builtin -ffreestanding -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include -g -O0 -fno-common -marm -mno-thumb-interwork -march=armv7-a -Wall -Wstrict-prototypes -D__KERNEL__ -D__SO3__ -Iinclude -fno-builtin -ffreestanding -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include -I. -I./lib/libfdt  -Iarch/arm/include/ -Iarch/arm/vexpress/include/	  -c -o drivers/mmc/mmc.o drivers/mmc/mmc.c

source_drivers/mmc/mmc.o := drivers/mmc/mmc.c

deps_drivers/mmc/mmc.o := \
    $(wildcard include/config/spl/build.h) \
    $(wildcard include/config/spl/libcommon/support.h) \
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
  include/mmc.h \
    $(wildcard include/config/sys/mmc/max/blk/count.h) \
  include/list.h \
  include/prefetch.h \
  arch/arm/include/asm/processor.h \
  include/part.h \
    $(wildcard include/config/sys/64bit/lba.h) \
    $(wildcard include/config/lba48.h) \
  include/heap.h \
  include/sizes.h \
  include/div64.h \
  include/delay.h \
  arch/arm/include/asm/byteorder.h \
  include/byteorder/little_endian.h \
  include/byteorder/swab.h \
  include/byteorder/generic.h \
  drivers/mmc/mmc_private.h \

drivers/mmc/mmc.o: $(deps_drivers/mmc/mmc.o)

$(deps_drivers/mmc/mmc.o):
