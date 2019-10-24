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
 * - May 2017: Xavier Ruppen
 * - June 2017: Daniel Rossier
 *
 */

#ifndef PROCESS_H
#define PROCESS_H

#include <types.h>
#include <list.h>
#include <thread.h>
#include <schedule.h>
#include <elf-struct.h>
#include <sync.h>

#define PROC_MAX 64
#define PROC_THREAD_MAX 32

/* Maximum stack size for a process, including all thread stacks */
#define PROC_STACK_SIZE (PROC_THREAD_MAX * THREAD_STACK_SIZE)

#define FD_MAX 64

typedef enum { PROC_STATE_NEW, PROC_STATE_READY, PROC_STATE_RUNNING, PROC_STATE_WAITING, PROC_STATE_ZOMBIE } proc_state_t;
typedef unsigned int thread_t;

#define PROC_NAME_LEN 80


/* A page might be linked to several processes, hence this type */
typedef struct {
	struct list_head list;
	page_t *page;
} page_list_t;

struct pcb {
	int pid;
	char name[PROC_NAME_LEN];

	/* Initial entry point used to configure the PC */
	uint32_t bin_image_entry;

	/* Full descending stack - refers to a "full" word */
	uint32_t stack_top;

	/* Thread stack slots */
	bool stack_slotID[PROC_THREAD_MAX];

	/* Heap management */
	uint32_t heap_base;
	uint32_t heap_pointer;

	/* Heap top (?) heap_base ? */
	void *heap_top;

	/* Number of pages required by this process (including binary image) */
	size_t page_count;

	/* List of frames (physical pages) belonging to this process */
	struct list_head page_list;

	/* Process 1st-level page table */
	uint32_t *pgtable;

	int exit_status;

	/* Reference to the parent process */
	pcb_t *parent;

	/* Containing thread */
	tcb_t *main_thread;
	tcb_t *prev_main_thread;

	/* List of threads of this process, except the main thread which has a specific field <main_thread> */
	struct list_head threads;

	/* Process state */
	int state;

	/* Local file descriptors belonging to the process */
	int fd_array[FD_MAX];

	/* Used to integrate a global system list of all existing process (declared in schedule.c) */
	struct list_head list;

	/* Manage a completion until all running threads complete (used with pthread_exit()) */
	completion_t threads_active;

};
typedef struct pcb pcb_t;

extern struct list_head proc_list;

int get_user_stack_slot(pcb_t *pcb);
void free_user_stack_slot(pcb_t *pcb, int slotID);

void add_page_to_proc(pcb_t *pcb, page_t *page);

pcb_t *create_process(int (*start_routine) (void *), const char *name);

int do_exec(const char *filename, int argc, char **argv);
int do_execve(const char *filename, int argc, char **argv, char **envp);
int do_fork(void);
void do_exit(int exit_status);
int do_waitpid(uint32_t pid, uint32_t *wstatus, uint32_t options);
uint32_t do_sbrk(int increment);

pcb_t *find_proc_by_pid(uint32_t pid);

int proc_register_fd(int fd);
int proc_new_fd(pcb_t *pcb);

extern int __exec(const char *file, int argc, char *argv[]);

#endif /* PROCESS_H */
