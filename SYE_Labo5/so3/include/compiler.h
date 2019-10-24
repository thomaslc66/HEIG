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

#ifndef COMPILER_H
#define COMPILER_H

#if !defined(__GNUC__) || (__GNUC__ < 3)
#error Sorry, your compiler is too old/not recognized.
#endif

/* Type for `void *' pointers. */
typedef unsigned long int uintptr_t;

#define barrier()     __asm__ __volatile__("": : :"memory")

#define likely(x)     __builtin_expect((x),1)
#define unlikely(x)   __builtin_expect((x),0)

#ifdef __CHECKER__
#define __force __attribute__((force))
#define __bitwise __attribute__((bitwise))
#else
#define __force
#define __bitwise
#endif

#define inline        __inline__
#define always_inline __inline__ __attribute__ ((always_inline))
#define noinline      __attribute__((noinline))

#define __attribute_pure__  __attribute__((pure))
#define __attribute_const__ __attribute__((__const__))

#if __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 3)
#define __attribute_used__ __attribute__((__used__))
#else
#define __attribute_used__ __attribute__((__unused__))
#endif

#if __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4)
#define __must_check __attribute__((warn_unused_result))
#else
#define __must_check
#endif

#if __GNUC__ > 3
#define offsetof(a,b) __builtin_offsetof(a,b)
#else
#define offsetof(a,b) ((unsigned long)&(((a *)0)->b))
#endif

/* Force a compilation error if condition is true */
#define BUILD_BUG_ON(condition) ((void)sizeof(struct { int:-!!(condition); }))

/* &a[0] degrades to a pointer: a different type from an array */
#define __must_be_array(a) \
  BUILD_BUG_ON_ZERO(__builtin_types_compatible_p(typeof(a), typeof(&a[0])))

#ifdef GCC_HAS_VISIBILITY_ATTRIBUTE
/* Results in more efficient PIC code (no indirections through GOT or PLT). */
#pragma GCC visibility push(hidden)
#endif

/* This macro obfuscates arithmetic on a variable address so that gcc
   shouldn't recognize the original var, and make assumptions about it */
/*
 * Versions of the ppc64 compiler before 4.1 had a bug where use of
 * RELOC_HIDE could trash r30. The bug can be worked around by changing
 * the inline assembly constraint from =g to =r, in this particular
 * case either is valid.
 */
#define RELOC_HIDE(ptr, off)                    \
  ({ unsigned long __ptr;                       \
    __asm__ ("" : "=r"(__ptr) : "0"(ptr));      \
    (typeof(ptr)) (__ptr + (off)); })

/*
 * A trick to suppress uninitialized variable warning without generating any
 * code
 */
#define uninitialized_var(x) x = x

#endif /* COMPILER_H */
