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

#include <asm/processor.h>
#include <asm/types.h>
#include <compiler.h>
#include <thread.h>

/*
 * Make sure that the compiler and target are compatible.
 */
#if defined(__APCS_26__)
#error Sorry, your compiler targets APCS-26 but this kernel requires APCS-32
#endif
/*
 * GCC 3.0, 3.1: general bad code generation.
 * GCC 3.2.0: incorrect function argument offset calculation.
 * GCC 3.2.x: miscompiles NEW_AUX_ENT in fs/binfmt_elf.c
 *            (http://gcc.gnu.org/PR8896) and incorrect structure
 *	      initialisation in fs/jffs2/erase.c
 */
#if (__GNUC__ == 3 && __GNUC_MINOR__ < 3)
#error Your compiler is too buggy; it is known to miscompile kernels.
#error    Known good compilers: 3.3
#endif

/* Use marker if you need to separate the values later */

#define DEFINE(sym, val) \
        asm volatile("\n->" #sym " %0 " #val : : "i" (val))

#define BLANK() asm volatile("\n->" : : )

int main(void)
{
	BLANK();

	DEFINE(OFFSET_TCB_CPU_REGS, 	offsetof(tcb_t, cpu_regs));

	BLANK();

	DEFINE(OFFSET_R0,			offsetof(cpu_regs_t, r0));
	DEFINE(OFFSET_R1,			offsetof(cpu_regs_t, r1));
	DEFINE(OFFSET_R2,			offsetof(cpu_regs_t, r2));
	DEFINE(OFFSET_R3,			offsetof(cpu_regs_t, r3));
	DEFINE(OFFSET_R4,			offsetof(cpu_regs_t, r4));
	DEFINE(OFFSET_R5,			offsetof(cpu_regs_t, r5));
	DEFINE(OFFSET_R6,			offsetof(cpu_regs_t, r6));
	DEFINE(OFFSET_R7,			offsetof(cpu_regs_t, r7));
	DEFINE(OFFSET_R8,			offsetof(cpu_regs_t, r8));
	DEFINE(OFFSET_R9,			offsetof(cpu_regs_t, r9));
	DEFINE(OFFSET_R10,			offsetof(cpu_regs_t, r10));
	DEFINE(OFFSET_FP,			offsetof(cpu_regs_t, fp));
	DEFINE(OFFSET_IP,			offsetof(cpu_regs_t, ip));
	DEFINE(OFFSET_SP,			offsetof(cpu_regs_t, sp));
	DEFINE(OFFSET_LR,			offsetof(cpu_regs_t, lr));
	DEFINE(OFFSET_PC,			offsetof(cpu_regs_t, pc));
	DEFINE(OFFSET_PSR,			offsetof(cpu_regs_t, psr));

	BLANK();

	return 0;
}

