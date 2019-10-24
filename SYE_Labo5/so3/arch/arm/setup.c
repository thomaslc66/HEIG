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
 * - 2014-2017: Daniel Rossier
 *
 * Low-level ARM-specific setup
 */

#include <tinyprintf.h>
#include <memory.h>
#include <driver.h>

#include <asm/processor.h>
#include <asm/setup.h>
#include <asm/hardware/irq.h>
#include <asm/mmu.h>

extern unsigned char __irq_stack_start[];

unsigned int processor_id;

/*
 * Only 3 32-bit fields are sufficient (see exception.S)
 */
struct stack {
	u32 irq[3];
	u32 abt[3];
	u32 und[3];
	u32 fiq[3];
} ____cacheline_aligned;

struct stack stacks;

/*
 * Setup exceptions stacks for all modes except SVC and USR
 */
void setup_exception_stacks(void) {
	struct stack *stk = &stacks;

	/* Need to set the CPU in the different modes and back to SVC at the end */
	__asm__ (
		"msr	cpsr_c, %1\n\t"
		"add	r14, %0, %2\n\t"
		"mov	sp, r14\n\t"
		"msr	cpsr_c, %3\n\t"
		"add	r14, %0, %4\n\t"
		"mov	sp, r14\n\t"
		"msr	cpsr_c, %5\n\t"
		"add	r14, %0, %6\n\t"
		"mov	sp, r14\n\t"
		"msr	cpsr_c, %7\n\t"
		"add	r14, %0, %8\n\t"
		"mov	sp, r14\n\t"
		"msr	cpsr_c, %9"
		    :
		    : "r" (stk),
		      "I" (PSR_F_BIT | PSR_I_BIT | IRQ_MODE), "I" (offsetof(struct stack, irq[0])),
		      "I" (PSR_F_BIT | PSR_I_BIT | ABT_MODE), "I" (offsetof(struct stack, abt[0])),
		      "I" (PSR_F_BIT | PSR_I_BIT | UND_MODE), "I" (offsetof(struct stack, und[0])),
		      "I" (PSR_F_BIT | PSR_I_BIT | FIQ_MODE), "I" (offsetof(struct stack, fiq[0])),
		      "I" (PSR_F_BIT | PSR_I_BIT | SVC_MODE)
		    : "r14");

}

/*
 * Low-level initialization before the main boostrap process.
 */
void setup_arch(void) {

	/* Clear BSS */
	clear_bss();

	/* Keep a reference to the 1st-level system page table */
#ifdef CONFIG_MMU
	__sys_l1pgtable = (unsigned int *) (CONFIG_RAM_BASE + L1_SYS_PAGE_TABLE_OFFSET);
#endif

	/* Set up the different stacks according to CPU mode */
	setup_exception_stacks();

	/* A low-level UART should be initialized here so that subsystems initialization (like MMC) can already print out logs ... */

}
