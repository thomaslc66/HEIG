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
 *
 * - 2014: Romain Bornet
 * - 2014-2017: Daniel Rossier (daniel.rossier@heig-vd.ch)
 *
 */

#if 0
#define DEBUG
#endif

#include <common.h>
#include <tinyprintf.h>
#include <calibrate.h>
#include <schedule.h>
#include <memory.h>
#include <mmc.h>
#include <driver.h>
#include <vfs.h>
#include <process.h>

#include <asm/atomic.h>
#include <asm/setup.h>
#include <asm/hardware/timer.h>
#include <asm/hardware/irq.h>

#include <asm/mmu.h>

#include <apps/main_thread.h>

void kernel_panic(void)
{
	printk("%s: entering infinite loop...\n", __func__);

#ifdef CONFIG_VEXPRESS
	{
		extern void send_qemu_halt(void);
		send_qemu_halt();
	}
#endif

	while (1);
}

void _bug(char *file, int line)
{
	printk("BUG in %s at line: %d\n", file, line); \
	kernel_panic();
}

/*
 * Initial (root) process which will start the first process running in SO3.
 * The process is running in user mode.
 */
int root_proc(void *args)
{
	printk("SO3: starting the initial process (shell) ...\n\n\n");


	/* Start the first process */
	__exec("sh.elf", 0, NULL);

	/* We normally never runs here, if the exec() succeeds... */
	printk("so3: No init proc (shell) found ...");
	kernel_panic();

	return 0; /* Make gcc happy ;-) */
}

int rest_init(void *dummy) {

	/* Start the idle thread */
	tcb_idle = kernel_thread(thread_idle, "idle", NULL);

	/* Start a first SO3 thread (main app thread) */
#if defined(CONFIG_THREAD_ENV)

	kernel_thread(main_kernel, "main_kernel", NULL);

	thread_exit(0);

#elif defined(CONFIG_PROC_ENV)

	/* Launch the root process (should be the shell...) */
	create_process(root_proc, "root_proc");

	/* We should never reach this ... */
	BUG();
#else
#error "Can not start initial SO3 environment"
#endif

	return 0;
}

void kernel_start(void) {

	/* Basic low-level initialization */
	setup_arch();

	printk("\n\n********** Smart Object Oriented SO3 Operating System **********\n");
	printk("Copyright (c) 2014-2017 REDS Institute, HEIG-VD, Yverdon\n");
	printk("Copyright (c) 2016-2017 Sootech SA\n");
	printk("Version 2017.2.0\n");

	printk("\n\nNow bootstraping the kernel ...\n");

	/* Memory manager subsystem initialization */
	memory_init();

	/* Interrupt management subsystem initialization */
	irq_init();

	init_driver_from_dtb();

	DBG("******** SO3 - Smart Object Oriented OS ********\n");
	DBG("Kernel is running !!!\n");
	DBG("************************************************\n\n");

	vfs_init();

	/* Scheduler init */
	scheduler_init();

	local_irq_enable();
	calibrate_delay();

	/*
	 * Perform the rest of bootstrap sequence in a separate thread, so that
	 * we can rely on the scheduler for subsequent threads.
	 */
	kernel_thread(rest_init, "so3_boot", NULL);

	/*
	 * We loop forever, just the time the scheduler gives the hand to a ready thread.
	 * After that, this code will never be executed anymore ...
	 */

	while (true) 
		__asm("wfi");
}
