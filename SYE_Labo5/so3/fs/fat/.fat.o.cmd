cmd_fs/fat/fat.o := arm-linux-gnueabihf-gcc -Wp,-MD,fs/fat/.fat.o.d  -Iinclude  -I.  -include include/generated/autoconf.h -D__KERNEL__ -D__SO3__ -Iinclude -fno-builtin -ffreestanding -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include -g -O0 -fno-common -marm -mno-thumb-interwork -march=armv7-a -Wall -Wstrict-prototypes -D__KERNEL__ -D__SO3__ -Iinclude -fno-builtin -ffreestanding -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/5/include -I. -I./lib/libfdt  -Iarch/arm/include/ -Iarch/arm/vexpress/include/	  -c -o fs/fat/fat.o fs/fat/fat.c

source_fs/fat/fat.o := fs/fat/fat.c

deps_fs/fat/fat.o := \
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
  include/errno.h \
  include/fat/fat.h \
  include/vfs.h \
  include/stat.h \
  include/fat/ff.h \
  include/fat/integer.h \
  include/fat/ffconf.h \
  include/dirent.h \
  include/time.h \
  include/heap.h \
  include/sizes.h \

fs/fat/fat.o: $(deps_fs/fat/fat.o)

$(deps_fs/fat/fat.o):
