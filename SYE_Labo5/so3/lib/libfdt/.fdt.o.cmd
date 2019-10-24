cmd_lib/libfdt/fdt.o := arm-linux-gnueabihf-gcc -Wp,-MD,lib/libfdt/.fdt.o.d  -Iinclude  -I.  -include include/generated/autoconf.h -D__KERNEL__ -D__SO3__ -Iinclude -fno-builtin -ffreestanding -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include -g -O0 -fno-common -marm -mno-thumb-interwork -march=armv7-a -Wall -Wstrict-prototypes -D__KERNEL__ -D__SO3__ -Iinclude -fno-builtin -ffreestanding -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include -I. -I./lib/libfdt  -Iarch/arm/include/ -Iarch/arm/vexpress/include/	  -c -o lib/libfdt/fdt.o lib/libfdt/fdt.c

source_lib/libfdt/fdt.o := lib/libfdt/fdt.c

deps_lib/libfdt/fdt.o := \
  lib/libfdt/libfdt_env.h \
  include/stddef.h \
  include/string.h \
  include/compiler.h \
  include/types.h \
  arch/arm/include/asm/types.h \
  arch/arm/include/asm/cache.h \
  lib/libfdt/fdt.h \
  lib/libfdt/libfdt.h \
  lib/libfdt/libfdt_env.h \
  lib/libfdt/libfdt_internal.h \
  include/fdt.h \
  include/memory.h \
    $(wildcard include/config/kernel/virt/addr.h) \
    $(wildcard include/config/ram/base.h) \
  arch/arm/include/asm/memory.h \
  lib/libfdt/libfdt.h \

lib/libfdt/fdt.o: $(deps_lib/libfdt/fdt.o)

$(deps_lib/libfdt/fdt.o):
