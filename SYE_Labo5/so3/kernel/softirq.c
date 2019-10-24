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
 *
 * Contributors:
 *
 * - 2015-2017 : Daniel Rossier
 *
 */

#include <bitops.h>
#include <types.h>
#include <spinlock.h>
#include <softirq.h>

uint32_t softirq_bitmap;

static softirq_handler softirq_handlers[NR_SOFTIRQS];

DEFINE_SPINLOCK(softirq_pending_lock);

/*
 * Perform actions of related pending softirqs if any.
 */
void do_softirq(void)
{
	unsigned int i;
	unsigned int pending;
	unsigned int loopmax;

	loopmax = 0;

	for ( ; ; )
	{
		spin_lock(&softirq_pending_lock);

		/* Any pending softirq ? */
		if ((pending = softirq_bitmap) == 0) {
			spin_unlock(&softirq_pending_lock);
			break;
		}

		i = find_first_bit(&pending, BITS_PER_INT);

		if (loopmax > 100)   /* Probably something wrong ;-) */
			printk("%s: Warning trying to process softirq for quite a long time (i = %d)...\n", __func__, i);

		clear_bit(i, (unsigned long *) &softirq_bitmap);

		spin_unlock(&softirq_pending_lock);

		(*softirq_handlers[i])();

		loopmax++;
	}
}

void register_softirq(int nr, softirq_handler handler)
{
    ASSERT(nr < NR_SOFTIRQS);

    softirq_handlers[nr] = handler;
}


void raise_softirq(unsigned int nr)
{
  set_bit(nr, (unsigned long *) &softirq_bitmap);
}


void softirq_init(void)
{
  spin_lock_init(&softirq_pending_lock);
}
