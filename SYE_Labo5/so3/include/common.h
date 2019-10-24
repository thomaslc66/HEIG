/*
 *
 * ----- SO3 Smart Object Oriented (SOO) Operating System -----
 *
 * Copyright (c) 2016,2017 Sootech SA, Switzerland
 * Copyright (c) 2014, 2015, 2016, 2017 REDS Institute, HEIG-VD, Switzerland
 * 
 * This software is released under the MIT License whose terms are defined hereafter.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR 
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef COMMON_H
#define COMMON_H

#include <tinyprintf.h>
#include <fdt.h>
#include <linker.h>

#define unlikely(x)   __builtin_expect((x),0)

extern uint32_t __end;

#ifdef DEBUG
#undef DBG
#define DBG(fmt, ...) \
    do { \
		printk("%s:%i > "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__); \
    } while(0)
#else
#define DBG(fmt, ...)
#endif

#define DIV_ROUND_CLOSEST(x, divisor)(                  \
 {                                                       \
   typeof(x) __x = x;                              \
   typeof(divisor) __d = divisor;                  \
     (((typeof(x))-1) > 0 ||                         \
     ((typeof(divisor))-1) > 0 || (__x) > 0) ?      \
       (((__x) + ((__d) / 2)) / (__d)) :       \
       (((__x) - ((__d) / 2)) / (__d));        \
 }                                                       \
)

#define max(a, b) ({\
		typeof(a) _a = a;\
		typeof(b) _b = b;\
		_a > _b ? _a : _b; })

#define min(a, b) ({\
		typeof(a) _a = a;\
		typeof(b) _b = b;\
		_a < _b ? _a : _b; })

/**
 * container_of - cast a member of a structure out to the containing structure
 *
 * @ptr:        the pointer to the member.
 * @type:       the type of the container struct this is embedded in.
 * @member:     the name of the member within the struct.
 *
 */
#define container_of(ptr, type, member) ({ \
  typeof( ((type *)0)->member ) *__mptr = (ptr); \
  (type *)( (char *)__mptr - offsetof(type,member) );})

void kernel_panic(void);
void _bug(char *file, int line);

#define BUG()	_bug(__FILE__, __LINE__)
#define BUG_ON(p)  do { if (unlikely(p)) BUG();  } while (0)

#define assert_failed(p)                                        \
do {                                                            \
  printk("Assertion '%s' failed, line %d, file %s\n", p ,     \
                    __LINE__, __FILE__);                         \
  kernel_panic();                                             \
} while (0)


#define ASSERT(p) \
     do { if ( unlikely(!(p)) ) assert_failed(#p); } while (0)

void dump_heap(const char *info);

#endif /* COMMON_H */
