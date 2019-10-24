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
 * - Daniel Rossier (2015-2017)
 *
 * This file contains some piece of code for various tests in SO3.
 */

#include <thread.h>
#include <mutex.h>
#include <tinyprintf.h>
#include <vfs.h>
#include <process.h>

#include <asm/hardware/timer.h>

struct mutex lock;

static volatile int count = 0;
int counter;

char serial_getc(void);
int serial_gets(char *buf, int len);
int serial_puts(char *buf, int len);


int thread_fn1(void *arg)
{
	/* FIXME: calling printk from user space crashes.
	 * We should have a write syscall on stdout. */
	printk("%s: hello\n", __func__);
	while (1); /* FIXME: implement thread_finish() and thread_join() properly when removing this infinite loop */

#if 0
	printk("acquiring lock for job %d\n", counter);
#if 0
	mutex_lock(&lock);
#endif

	counter += 1;
	printk("\n Job %d started\n", counter);


	for (i = 0; i < 100000; i++)
		count++;

	printk("\n Job %d finished\n", counter);

#if 0
	mutex_unlock(&lock);
#endif
#endif

	return 0;
}

int thread_example(void *arg)
{
	long long ii = 0;

	printk("### entering thread_example.\n");

	for (ii = 0; ii < 100000; ii++)
		count++;

	return 0;
}

int fn1(void *args) {
	int i = 0;

	printk("Thread #1\n");
	while (1) {
		printk("--> th 1: %d\n", i++);
	}

	return 0;
}

int fn2(void *args) {
	int i = 0;

	printk("Thread #1\n");
	while (1) {
		printk("--> th 2: %d\n", i++);
	}

	return 0;
}

extern int schedcount;

/*
 * First SO3 main kernel thread
 */
int main_kernel(void *args)
{
#if 0
	int ret;
	char buf[128];
	int fd;
	tcb_t *t1, *t2;
#endif

#if 0
	tcb_t *thread[10];
	int tid;
	int i;
	unsigned long flags;
#endif

#if 0
	do_ls("mmc", "0:1", FS_TYPE_FAT, "/");
#endif

#if 0
	fd = fd_open("hello.txt", O_RDONLY);
	printk("%s: fd = %d\n", __func__, fd);
	ret = fd_read(fd, buf, 128);
	printk("%s: read %d characters: %s\n", __func__, ret, buf);
#endif

#if 0
	mutex_init(&lock);
#endif

	/* Kernel never returns ! */
	printk("***********************************************\n");
	printk("Going to infinite loop...\n");
	printk("Kill Qemu with CTRL-a + x or reset the board\n");
	printk("***********************************************\n");

	kernel_thread(fn1, "fn1", NULL);
	kernel_thread(fn2, "fn2", NULL);

	while (1);
#if 0
	while (1) {
		ret = fd_read(STDIN, buf, 10);
		printk("%s: read: %s\n", __func__, buf);
        }
#endif

	return 0;
}

