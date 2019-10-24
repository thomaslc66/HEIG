cmd_lib/vsprintf.o := arm-linux-gnueabihf-gcc -Wp,-MD,lib/.vsprintf.o.d  -Iinclude  -I.  -include include/generated/autoconf.h -D__KERNEL__ -D__SO3__ -Iinclude -fno-builtin -ffreestanding -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include -g -O0 -fno-common -marm -mno-thumb-interwork -march=armv7-a -Wall -Wstrict-prototypes -D__KERNEL__ -D__SO3__ -Iinclude -fno-builtin -ffreestanding -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include -I. -I./lib/libfdt  -Iarch/arm/include/ -Iarch/arm/vexpress/include/	  -c -o lib/vsprintf.o lib/vsprintf.c

source_lib/vsprintf.o := lib/vsprintf.c

deps_lib/vsprintf.o := \
  /usr/lib/gcc/x86_64-linux-gnu/5/include/stdarg.h \
  include/types.h \
  arch/arm/include/asm/types.h \
  arch/arm/include/asm/cache.h \
  include/string.h \
  include/stddef.h \
  include/ctype.h \
  include/heap.h \
  include/sizes.h \
  include/errno.h \
  include/common.h \
  include/tinyprintf.h \
    $(wildcard include/config/debug/printk.h) \
  include/fdt.h \
  include/memory.h \
    $(wildcard include/config/kernel/virt/addr.h) \
    $(wildcard include/config/ram/base.h) \
  arch/arm/include/asm/memory.h \
  lib/libfdt/libfdt.h \
  lib/libfdt/libfdt_env.h \
  include/compiler.h \
  lib/libfdt/fdt.h \
  include/linker.h \
  include/div64.h \

lib/vsprintf.o: $(deps_lib/vsprintf.o)

$(deps_lib/vsprintf.o):
