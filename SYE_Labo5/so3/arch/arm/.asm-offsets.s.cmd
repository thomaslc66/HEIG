cmd_arch/arm/asm-offsets.s := arm-linux-gnueabihf-gcc -Wp,-MD,arch/arm/.asm-offsets.s.d  -Iinclude  -I.  -include include/generated/autoconf.h -D__KERNEL__ -D__SO3__ -Iinclude -fno-builtin -ffreestanding -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include -g -O0 -fno-common -marm -mno-thumb-interwork -march=armv7-a -Wall -Wstrict-prototypes -D__KERNEL__ -D__SO3__ -Iinclude -fno-builtin -ffreestanding -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include -I. -I./lib/libfdt  -Iarch/arm/include/ -Iarch/arm/vexpress/include/	  -fverbose-asm -S -o arch/arm/asm-offsets.s arch/arm/asm-offsets.c

source_arch/arm/asm-offsets.s := arch/arm/asm-offsets.c

deps_arch/arm/asm-offsets.s := \
  arch/arm/include/asm/processor.h \
  include/types.h \
  arch/arm/include/asm/types.h \
  arch/arm/include/asm/cache.h \
  include/compiler.h \
  include/thread.h \
  arch/arm/include/asm/memory.h \
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
  lib/libfdt/fdt.h \
  include/linker.h \
  include/prefetch.h \
  include/schedule.h \

arch/arm/asm-offsets.s: $(deps_arch/arm/asm-offsets.s)

$(deps_arch/arm/asm-offsets.s):
