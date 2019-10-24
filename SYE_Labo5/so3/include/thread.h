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

#ifndef THREAD_H
#define THREAD_H

#include <asm/memory.h>

#define	THREAD_MAX		32
#define THREAD_NAME_LEN 	80

#define	THREAD_STACK_SIZE	(32 * 1024)

#ifndef __ASSEMBLY__

#include <types.h>
#include <list.h>
#include <schedule.h>

typedef enum { THREAD_STATE_NEW, THREAD_STATE_READY, THREAD_STATE_RUNNING, THREAD_STATE_WAITING, THREAD_STATE_ZOMBIE } thread_state_t;
typedef unsigned int thread_t;

typedef struct cpu_regs {
	__u32   r0;
	__u32   r1;
	__u32   r2;
	__u32   r3;
	__u32   r4;
	__u32   r5;
	__u32   r6;
	__u32   r7;
	__u32   r8;
	__u32   r9;
	__u32   r10;
	__u32   fp;
	__u32   ip;
	__u32   sp;
	__u32   lr;
	__u32   pc;
	__u32   psr;
} cpu_regs_t;

extern unsigned int __stack_top;

extern void thread_epilogue(void);

struct queue_thread;
typedef struct pcb pcb_t;
/*
 * Task Control Block
 *
 * The structure is a self-contained list.
 */
struct tcb {
	int tid;
	char name[THREAD_NAME_LEN];

	/* Threaded function */
	int (*th_fn) (void *);
	void *th_arg;

	thread_t state;
	int stack_slotID; /* Thread kernel slot ID */

	/* Reference to the process, if any - typically NULL for kernel threads */
	pcb_t *pcb;

	int exit_status;

	struct list_head list;  /* List of threads belonging to a process */

	/* Join queue to handle threads waiting on it */
	struct list_head joinQueue;

	cpu_regs_t cpu_regs;
};
typedef struct tcb tcb_t;

void threads_init(void);

int do_thread_create(uint32_t *pthread_id, uint32_t attr_p, uint32_t thread_fn, uint32_t arg_p);
int do_thread_join(uint32_t pthread_id, int **value_p);
void do_thread_exit(int *exit_status);

tcb_t *kernel_thread(int (*start_routine) (void *), const char *name, void *arg);
tcb_t *user_thread(int (*start_routine) (void *), const char *name, void *arg, pcb_t *pcb);

int thread_join(tcb_t *tcb);
void thread_exit(int *exit_status);
void clean_thread(tcb_t *tcb);

int thread_idle(void *dummy);

uint32_t get_kernel_stack_top(uint32_t slotID);

extern void __switch_context(tcb_t *prev, tcb_t *next);
extern void __thread_prologue_kernel(void);
extern void __thread_prologue_user(void);
extern void __thread_prologue_user_pre_launch(void);

char *print_state(struct tcb *tcb);

#endif /* __ASSEMBLY__ */

#endif /* THREAD_H */
