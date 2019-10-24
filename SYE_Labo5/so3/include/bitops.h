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
 * Contributors:
 * - Daniel Rossier, May 2017
 *
 */

#ifndef BITOPS_H
#define BITOPS_H

#include <types.h>
#include <asm/processor.h>

#define BIT_MASK(nr)		(1UL << ((nr) % BITS_PER_INT))
#define BIT_WORD(nr)		((nr) / BITS_PER_INT)


extern int _find_first_zero_bit(const void *p, unsigned size);
extern int _find_next_zero_bit(const void *p, int size, int offset);
extern int _find_first_bit(const unsigned int *p, unsigned size);
extern int _find_next_bit(const unsigned int *p, int size, int offset);

#define find_first_zero_bit(p, sz)       _find_first_zero_bit(p, sz)
#define find_next_zero_bit(p, sz, off)    _find_next_zero_bit(p, sz, off)
#define find_first_bit(p, sz)            _find_first_bit(p, sz)
#define find_next_bit(p, sz, off)         _find_next_bit(p, sz, off)

/*
 * These functions are the basis of our bit ops.
 *
 * First, the atomic bitops. These use native endian.
 */
static inline void ____atomic_set_bit(unsigned int bit, volatile unsigned long *p)
{
	uint32_t flags;
	unsigned long mask = 1UL << (bit & 31);

	p += bit >> 5;

	flags = local_irq_save();
	*p |= mask;
	local_irq_restore(flags);
}

static inline void ____atomic_clear_bit(unsigned int bit, volatile unsigned long *p)
{
	uint32_t flags;
	unsigned long mask = 1UL << (bit & 31);

	p += bit >> 5;

	flags = local_irq_save();
	*p &= ~mask;
	local_irq_restore(flags);
}

#define set_bit(nr,p)                   ____atomic_set_bit(nr, p)
#define clear_bit(nr,p)                 ____atomic_clear_bit(nr, p)

extern void change_bit(int nr, volatile void * addr);

static inline void __change_bit(int nr, volatile void *addr)
{
	unsigned long mask = BIT_MASK(nr);
	unsigned long *p = ((unsigned long *)addr) + BIT_WORD(nr);

	*p ^= mask;
}

static inline int __test_and_set_bit(int nr, volatile void *addr)
{
	unsigned long mask = BIT_MASK(nr);
	unsigned long *p = ((unsigned long *)addr) + BIT_WORD(nr);
	unsigned long old = *p;

	*p = old | mask;
	return (old & mask) != 0;
}

static inline int test_and_set_bit(int nr, volatile void * addr)
{
	uint32_t flags;
	int out;

	flags = local_irq_save();
	out = __test_and_set_bit(nr, addr);
	local_irq_restore(flags);

	return out;
}

static inline int __test_and_clear_bit(int nr, volatile void *addr)
{
	unsigned long mask = BIT_MASK(nr);
	unsigned long *p = ((unsigned long *)addr) + BIT_WORD(nr);
	unsigned long old = *p;

	*p = old & ~mask;
	return (old & mask) != 0;
}

static inline int test_and_clear_bit(int nr, volatile void * addr)
{
	uint32_t flags;
	int out;

	flags = local_irq_save();
	out = __test_and_clear_bit(nr, addr);
	local_irq_restore(flags);

	return out;
}

extern int test_and_change_bit(int nr, volatile void * addr);

static inline int __test_and_change_bit(int nr, volatile void *addr)
{
	unsigned long mask = BIT_MASK(nr);
	unsigned long *p = ((unsigned long *)addr) + BIT_WORD(nr);
	unsigned long old = *p;

	*p = old ^ mask;
	return (old & mask) != 0;
}

/*
 * This routine doesn't need to be atomic.
 */
static inline int test_bit(int nr, const void * addr)
{
    return ((unsigned char *) addr)[nr >> 3] & (1U << (nr & 7));
}


#endif /* BITOPS_H */
