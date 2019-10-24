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
 * - April-June 2017: Xavier Ruppen
 * - June 2017: Alexandre Malki
 * - June 2017: Daniel Rossier
 *
 */

#include <asm/syscall.h>
#include <common.h>
#include <process.h>
#include <thread.h>
#include <vfs.h>
#include <pipe.h>
#include <heap.h>
#include <process.h>

static uint32_t *errno_addr = NULL;

extern void __get_syscall_args_ext(uint32_t *syscall_no, uint32_t **__errno_addr);

extern void test_malloc(int test_no);

/*
 * Set the (user space) virtual address of the global <errno> variable which is defined in the libc.
 * <errno> is used to keep a error number in case of syscall execution failure.
 */
void set_errno_addr(uint32_t *addr) {
	errno_addr = addr;
}

/*
 * Set the errno to a specific value defined in errno.h
 */
void set_errno(uint32_t val) {
	if (errno_addr != NULL)
		*errno_addr = val;
}

/*
 * Process syscalls according to the syscall number passed in r7.
 */

int syscall_handle(uint32_t r0, uint32_t r1, uint32_t r2, uint32_t r3)
{
	int result = -1;
	uint32_t syscall_no, *__errno_addr;

	/* Get addtional args of the syscall according to the ARM & SO3 ABI */
	__get_syscall_args_ext(&syscall_no, &__errno_addr);

//#warning no re-entrant at the moment...

	set_errno_addr(__errno_addr);

	switch (syscall_no) {

#ifdef CONFIG_MMU
		case SYSCALL_EXIT:
			do_exit(r0);
			break;

		case SYSCALL_EXEC:
			/* FIXME: copy_from_user() etc. */
			result = do_exec((const char *) r0, (int) r1, (char **) r2);
			break;
		
		case SYSCALL_FORK:
			result = do_fork();
			break;

		case SYSCALL_WAITPID:
			result = do_waitpid(r0, (uint32_t *) r1, r2);
			break;
#endif /* CONFIG_MMU */

		case SYSCALL_READ:
			/* FIXME: copy_from_user() */
			result = do_read(r0, (void *) r1, r2);
			break;

		case SYSCALL_WRITE:
			/* FIXME: copy_to_user() */
			result = do_write(r0, (void *) r1, r2);
			break;

		case SYSCALL_OPEN:
			result = do_open((const char *) r0, r1);
			break;

		case SYSCALL_CLOSE:
			do_close((int) r0);
			result = 0;
			break;

		case SYSCALL_THREAD_CREATE:
			result = do_thread_create((uint32_t *) r0, r1, r2, r3);
			break;

		case SYSCALL_THREAD_JOIN:
			result = do_thread_join(r0, (int **) r1);
			break;
	
		case SYSCALL_THREAD_EXIT:
			do_thread_exit((int *) r0);
			result = 0;
			break;

		case SYSCALL_READDIR:
			/* FIXME: copy_to_user() */
			result = (int ) do_readdir((int) r0);
			break;

		case SYSCALL_IOCTL:
			result = (int) do_ioctl((int) r0, (unsigned long) r1, (unsigned long) r2);
			break;

#ifdef CONFIG_IPC_PIPE
		case SYSCALL_PIPE:
			result = do_pipe((int*) r0);
			break;

#endif /* CONFIG_IPC_PIPE */

		case SYSCALL_DUP:
			result = do_dup((int) r0);
			break;

		case SYSCALL_DUP2:
			result = do_dup2((int) r0, (int) r1);
			break;

		case SYSCALL_STAT:
			result = do_stat((char *) r0, (struct stat *) r1);
			break;
		case SYSCALL_SBRK:
			result = do_sbrk((unsigned long) r0);
			break;

		case SYSCALL_EXECVE:
			result = do_execve((const char *) r0, (int) r1, (char **) r2, (char **) r3);
			break;

	/* This is a first attempt of mutex syscall implementation.
	 * Mainly used for debugging purposes (kernel mutex validation) at the moment ... */

		case SYSCALL_MUTEX_INIT:
			result = do_mutex_init();
			break;

		case SYSCALL_MUTEX_LOCK:
			result = do_mutex_lock();
			break;

		case SYSCALL_MUTEX_UNLOCK:
			result = do_mutex_unlock();
			break;
#ifdef CONFIG_APP_TEST_MALLOC
			case SYSINFO_TEST_MALLOC:
				test_malloc(r1);
				break;
#endif

			default:
				printk("%s: unhandled syscall: %d\n", __func__, syscall_no);
			break;
        }

	return result;
}
