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
 * - April-May 2017: Xavier Ruppen, Daniel Rossier
 *
 */

#if 0
#define DEBUG
#endif

#include <types.h>
#include <common.h>
#include <thread.h>
#include <process.h>
#include <schedule.h>
#include <heap.h>
#include <elf.h>
#include <memory.h>
#include <vfs.h>
#include <wait.h>

#include <asm/syscall.h>
#include <asm/mmu.h>
#include <asm/processor.h>
#include <asm/cacheflush.h>

/* We should maintain a bitmap of all pids in use in case we wrap around.
 * Just assume we won't ever spawn 2^32 processes for now. */

/* pid_current starts at 1 since pid 0 is used by fork() to test against the child process */
static uint32_t pid_current = 1;
static pcb_t *root_process = NULL; /* root process */

/* Used to update regs during fork */
extern void __save_context(tcb_t *newproc, uint32_t stack_addr);

/* only the following sections are supported */
#define SUPPORTED_SECTION_COUNT 6
static const char *supported_section_names[SUPPORTED_SECTION_COUNT] = {
		".text",
		".rodata",
		".data",
		".sbss",
		".bss",
		".scommon",
};

/*
 * Find a process (pcb_t) from its pid.
 * Return NULL if no process as been found.
 */
pcb_t *find_proc_by_pid(uint32_t pid) {
	pcb_t *pcb;
	struct list_head *pos;

	list_for_each(pos, &proc_list)
	{
		pcb = list_entry(pos, pcb_t, list);
		if (pcb->pid == pid)
			return pcb;

	}

	/* Not found */
	return NULL;
}


/* @brief This function will retrieve a unused fd.
 *		It will loop from the beginning of the local fd table
 *		to avoid fragmentation
 */
int proc_new_fd(pcb_t *pcb)
{
	unsigned i;

	for (i = 0; i < FD_MAX ; i++)
		if (pcb->fd_array[i] == -1)
			return i;

	return -1;
}

/*
 * Remove a process from the global list and free the PCB struct.
 */
void remove_proc(pcb_t *pcb) {
	struct list_head *pos, *p;
	pcb_t *cur;

	list_for_each_safe(pos, p, &proc_list)
	{
		cur = list_entry(pos, pcb_t, list);

		if (cur == pcb) {
			list_del(pos);

			free(cur);
			return ;
		}
	}
}

/*
 * Create a new process with its PCB and basic contents.
 */
pcb_t *new_process(void)
{
	unsigned int i;
	pcb_t *pcb;

	/* PCB allocation */
	pcb = malloc(sizeof(pcb_t));

	if (!pcb) {
		printk("%s: failed to allocate memory\n", __func__);
		kernel_panic();
	}
	memset(pcb, 0, sizeof(pcb_t));

	/* Init the list of pages */
	INIT_LIST_HEAD(&pcb->page_list);

	pcb->pid = pid_current++;

	for (i = 0; i < PROC_THREAD_MAX; i++)
		pcb->stack_slotID[i] = false;

	/* Init the list of child threads */
	INIT_LIST_HEAD(&pcb->threads);

	/* Process-related memory management */

	/* create the 1st level page table */
	pcb->pgtable = new_l1pgtable();
	if (!pcb->pgtable) {
		printk("%s: failed to create level 1 page table", __func__);
		kernel_panic();
	}

	/* Preserve the mapping to the high-1G kernel area */
	pgtable_copy_kernel_area(pcb->pgtable);

	/* Integrate the list of process */
	list_add_tail(&pcb->list, &proc_list);

	/* Initialize the completion used for managing running threads (helpful for pthread_exit()) */
	init_completion(&pcb->threads_active);

	return pcb;
}

/*
 * Initialize the (user space) process stack
 */
void reset_process_stack(pcb_t *pcb) {

	/* Set up the main process stack (including all thread stacks) */
	pcb->page_count = ALIGN_UP(PROC_STACK_SIZE, PAGE_SIZE) >> PAGE_SHIFT;

	/*
	 * The stack virtual top is under the page of arguments, from the top user space.
	 * The stack is full descending.
	 */
	pcb->stack_top = CONFIG_KERNEL_VIRT_ADDR - PAGE_SIZE;
}

void dump_proc_pages(pcb_t *pcb){
	page_list_t *cur;

	printk("----- Dump of pages belonging to proc: %d -----\n\n", pcb->pid);
	list_for_each_entry(cur, &pcb->page_list, list)
		printk("   -- page: %p  pfn: %x\n", cur->page, page_to_pfn(cur->page));
	printk("\n");
}


void add_page_to_proc(pcb_t *pcb, page_t *page) {
	page_list_t *page_list_entry;

	page_list_entry = malloc(sizeof(page_list_t));
	if (page_list_entry == NULL) {
		printk("%s: failed to allocate memory!\n", __func__);
		kernel_panic();
	}

	page_list_entry->page = page;

	/* Insert our page at the end of the list */
	list_add_tail(&page_list_entry->list, &pcb->page_list);

}

/*
 * Find available frames and do the mapping of a number of pages.
 */
static void allocate_page(pcb_t *pcb, uint32_t virt_addr, int nr_pages) {
	int i;
	page_t *page;

	/* Perform the mapping of a new physical memory region at the region started at @virt_addr  */
	for (i = 0; i < nr_pages; i++) {
		page = get_free_page();

		create_mapping(pcb->pgtable, virt_addr + (i * PAGE_SIZE), pfn_to_phys(page_to_pfn(page)), PAGE_SIZE);

		add_page_to_proc(pcb, page);
	}
}

/*
 * Create a process from scratch, without fork'd. Typically used by the kernel main
 * at the end of the bootstrap.
 */
pcb_t *create_process(int (*start_routine)(void *), const char *name)
{
	pcb_t *pcb;
	uint32_t flags;
	int i;

	flags = local_irq_save();

	pcb = new_process();

	reset_process_stack(pcb);

	/* We map the initial user space process stack here, and fork() will inherit from this mapping */

	allocate_page(pcb, pcb->stack_top - (pcb->page_count * PAGE_SIZE), pcb->page_count);

	DBG("stack mapped at 0x%08x (size: %d bytes)\n", pcb->stack_top - (page_count * PAGE_SIZE), PROC_STACK_SIZE);

#warning set up argc & argv correctly for the root process...

	/* Start main thread */
	pcb->prev_main_thread = current();
	pcb->main_thread = user_thread(start_routine, name, NULL, pcb);

	/* init process? */
	if (!root_process)
		root_process = pcb;

	/* Init file descriptors to -1 */
	for (i = 0; i < FD_MAX; i++)
		pcb->fd_array[i] = -1;

	/* Set the file descriptors */
	pcb->fd_array[STDOUT] = STDOUT;
	pcb->fd_array[STDIN] = STDIN;
	pcb->fd_array[STDERR] = STDERR;

	/* At the end, the so3-boot thread which is running this function can disappear ... */
	thread_exit(0);

	local_irq_restore(flags);

	return pcb;
}


/*
 * Release all pages allocated to a process
 */
static void release_proc_pages(pcb_t *pcb) {
	struct list_head *pos, *q;
	page_list_t *cur;

	list_for_each_safe(pos, q, &pcb->page_list)
	{
		cur = list_entry(pos, page_list_t, list);

		if (pos->next->prev != pos) dump_proc_pages(pcb);
		list_del(pos);

		release_page(cur->page);
		free(cur);
	}
}

/*
 * Set up the PCB fields related to the binary image to be loaded.
 */
void setup_proc_image_replace(elf_img_info_t *elf_img_info, pcb_t *pcb, int argc, char **argv, char **envp)
{
	uint32_t page_count;
	uint32_t args_page_sz = PAGE_SIZE;
	char *args_p, *args_str_p, *str_tmp;
	char *envp_p;
	void *args;
	int i, j;

	/* FIXME: detect fragmented executable (error)? */
	/*
	 * Preserve the arguments issued from this configuration so that we
	 * can place them within their definitive place in the target image.
	 */
	args = malloc(args_page_sz);
	BUG_ON(args == NULL);

	memset(args, 0, args_page_sz);

	args_p = (char *) args;
	memcpy(args_p, &argc, sizeof(int));

	/* Name of the program + vars counter */
	args_p += sizeof(int);

	/* Store the array of strings */

	/* One address per string + one address per env + process name
	 * The proc name is stored right after the first pointer array.
	 * The first string is located right after the proc name.
	 * The fist env right after the strings.
	 */
	args_str_p = args_p + sizeof(char *) + argc*sizeof(char *);

	/* We reserve at least a pointer for the environment variables */
	args_str_p += sizeof(int);

	/* This is for environment variable allocation */
	if (envp)
		for (j = 0; envp[j] != NULL; j++)
			args_str_p = args_str_p + sizeof(char *);

	if (!argv) {
		args_p += sizeof(char *);

		/* We can already copy the process name */
		str_tmp = strcpy(args_str_p, pcb->name);

		args_str_p += strlen(str_tmp) + 1;
		memcpy(args + sizeof(char *), &str_tmp, sizeof(char *));
	}

	/* We loop through all the argc + 1:
	 * There are argc number of arguments and another one right after which
	 * holds the environment variables
	 */
	for (i = 0; i < (argc); i++) {
		memcpy(args_p, &args_str_p, sizeof(char *));
		strcpy(args_str_p, argv[i]);
		args_str_p += strlen(argv[i]) + 1;

		args_p += sizeof(char *);

		/* We check if the pointer do not exceed the page we
		 * allocated before */
		if (((uint32_t) args_str_p - (uint32_t) args) > args_page_sz) {
			DBG("Not enougth memory allocated\n");
			set_errno(ENOMEM);

			free(args);
			return;
		}
	}

	/* Environment variable table set right after the string data */
	envp_p = args_p + sizeof(char *);

	/* If the environment was passed */
	if (envp) {
		/* First retrieve the size of the env table*/
		for (i = 0; i < j; i++) {
			memcpy(envp_p , &args_str_p, sizeof(char *));
			strcpy(args_str_p, envp[i]);
			args_str_p += strlen(envp[i]) + 1;
			envp_p += 4;

			/* We check if pointer do not exceed the page we
			 * allocated before. */
			if (((uint32_t) args_str_p - (uint32_t) args) > args_page_sz) {
				DBG("Not enougth memory allocated\n");
				set_errno(ENOMEM);
				free(args);
				return;
			}
		}
	}

	/* Reset the process stack and page count */
	reset_process_stack(pcb);

	/* Release allocated pages in case of exec() within a fork'd process */
	/* The current binary image (which is a copy of the fork'd) must disappeared.
	 * Associated physical pages must be removed and freed. Stack area will be re-initialized.
	 */
	reset_l1pgtable(pcb->pgtable, false);

	/* Release all allocated pages for user space */
	release_proc_pages(pcb);

	/* We re-init the user space process stack here, and fork() will inherit from this mapping */

	allocate_page(pcb, pcb->stack_top - (pcb->page_count * PAGE_SIZE), pcb->page_count);

	DBG("stack mapped at 0x%08x (size: %d bytes)\n", pcb->stack_top - (page_count * PAGE_SIZE), PROC_STACK_SIZE);

	/* Initialize the pc register */
	pcb->bin_image_entry = (uint32_t) elf_img_info->header->e_entry;

	/* The first virtual page will not be mapped since it is the zero-page which
	 * is used to detect NULL pointer access. It has to raise a data abort exception.
	 * That's the reason why the linker script of a user application must start at 0x1000 (at the lowest).
	 */

	pcb->page_count += elf_img_info->segment_page_count;

	/* Map the elementary sections (text, data, bss) */
	allocate_page(pcb, (uint32_t) elf_img_info->header->e_entry, elf_img_info->segment_page_count);

	DBG("entry point: 0x%08x\n", elf_img_info->bin_image_entry);
	DBG("page count: 0x%08x\n", pcb->page_count);

	/* Maximum heap size */
	page_count = ALIGN_UP(HEAP_SIZE, PAGE_SIZE) >> PAGE_SHIFT;
	pcb->heap_base = (pcb->page_count + 1) * PAGE_SIZE;
	pcb->heap_pointer = pcb->heap_base;
	pcb->page_count += page_count;

	allocate_page(pcb, pcb->heap_base, page_count);

	DBG("heap mapped at 0x%08x (size: %d bytes)\n", pcb->heap_base, HEAP_SIZE);

	/* arguments will be stored in one more page */
	pcb->page_count++;

	allocate_page(pcb, CONFIG_KERNEL_VIRT_ADDR - PAGE_SIZE, 1);
	DBG("arguments mapped at 0x%08x (size: %d bytes)\n", CONFIG_KERNEL_VIRT_ADDR - PAGE_SIZE,  PAGE_SIZE);

	/* Prepare the arguments within the page reserved for this purpose. */

	memcpy((void *) (CONFIG_KERNEL_VIRT_ADDR - PAGE_SIZE), args, PAGE_SIZE);

	flush_tlb_all();
	cache_clean_flush();

	free(args);
}

/* load sections from each loadable segment into the process' virtual pages */
void load_process(elf_img_info_t *elf_img_info)
{
	uint32_t section_start, section_end;
	uint32_t segment_start, segment_end;
	int i, j, k;
	bool section_supported;

	/* Loading the different segments */
	for (i = 0; i < elf_img_info->header->e_phnum; i++)
	{
		if (elf_img_info->segments[i].p_type != PT_LOAD)
			/* Skip unloadable segments */
			continue;

		segment_start = elf_img_info->segments[i].p_offset;
		segment_end = segment_start + elf_img_info->segments[i].p_memsz;

		/* Sections */
		for (j = 0; j < elf_img_info->header->e_shnum; j++) {
			section_start = elf_img_info->sections[j].sh_offset;
			section_end = section_start + elf_img_info->sections[j].sh_size;

			/* Verify if the section is part of this segment */
			if ((section_start < segment_start) || (section_end > segment_end))
				continue;

			/* Not all sections are supported */
			section_supported = false;
			for (k = 0; k < SUPPORTED_SECTION_COUNT; k++) {
				if (!strcmp(elf_img_info->section_names[j], supported_section_names[k])) {
					section_supported = true;
					break;
				}
			}

			if (!section_supported)
				continue;

			/* Load this section into the process' virtual memory */
			if (elf_img_info->sections[j].sh_type == SHT_NOBITS)
				/* unless it were not stored in the file (.bss) */
				continue;

			/* Real load of contents in the user space memory of the process */
			DBG("Copying %x bytes from %p to virt addr: %x\n", pcb->sections[j].sh_size, (void *) (buffer + pcb->sections[j].sh_offset), pcb->sections[j].sh_addr);
			memcpy((void *) elf_img_info->sections[j].sh_addr, (void *) (elf_img_info->file_buffer + elf_img_info->sections[j].sh_offset), elf_img_info->sections[j].sh_size);

			/* FIXME: read-only bit if needed (Elf.java)? */
		}
	}
}

/*
 * do_exec() will replace the current binary image within the user space with a new one.
 */
int do_exec(const char *filename, int argc, char **argv)
{
	return do_execve(filename, argc, argv, NULL);
}

int do_execve(const char *filename, int argc, char **argv, char **envp)
{
	elf_img_info_t elf_img_info;
	pcb_t *pcb;
	uint32_t flags;
	int (*start_routine)(void *);
	queue_thread_t *cur;

	/* We do not support exec() from another thread than the main one */
	ASSERT(current() == current()->pcb->main_thread);

	flags = local_irq_save();

	/* Get the running process */
	pcb = current()->pcb;

	/* Keep the filename as process name */
	strcpy(pcb->name, filename);

	/* ELF parsing */
	elf_img_info.file_buffer = elf_load_buffer(filename);
	if (elf_img_info.file_buffer == NULL) {
		local_irq_restore(flags);
		set_errno(ENOENT);

		return -1;
	}

	elf_load_sections(&elf_img_info);
	elf_load_segments(&elf_img_info);

	/*
	 * If it is not the root process and the initial thread,
	 * replace the binary image of the process. - Prepare the page frames and mapped then in the virtual address space.
	 */
	setup_proc_image_replace(&elf_img_info, pcb, argc, argv, envp);

	/* process execution */
#warning do_exec() must be completed...
	/* TODO: close all fds except stdin stdout stderr -> including pipes (so keep all, end of process will terminate fds */

	/* Load the contents of ELF into the virtual memory space */
	load_process(&elf_img_info);

	/* Release the kernel buffer used to store the ELF binary image */
	elf_clean_image(&elf_img_info);

	/* Now, we need to create the main user thread associated to this binary image. */
	/* start main thread */
	start_routine = (int(*)(void *)) pcb->bin_image_entry;

	/* We start the new thread */
	pcb->prev_main_thread = pcb->main_thread; /* Necessary to perform a removal later on */
	pcb->main_thread = user_thread(start_routine, pcb->name, (void *) (CONFIG_KERNEL_VIRT_ADDR - PAGE_SIZE), pcb);

	/* Transfer the waiting thread if any */

	/* Make sure it is the main thread of the dying thread, i.e. another process is waiting on it (the parent) */
	if (!list_empty(&current()->joinQueue)) {
		cur = list_entry(current()->joinQueue.next, queue_thread_t, list);

		ASSERT(cur->tcb->pcb == current()->pcb->parent);

		/* Migrate the entry to the new main thread */
		list_move(&cur->list, &pcb->main_thread->joinQueue);

	}

	/* Now, make sure there is no other waiting threads on the dying thread */
	ASSERT(list_empty(&current()->joinQueue));

	/* Finishing the running thread. The final clean_thread() function will be
	 * called during the pre_launch_proc() part of prologue, based on the value of pcb->prev_main_thread.
	 */
	thread_exit(0);

	/* IRQs never restored here... */

	return 0;
}

/*
 * Clean the previous running threads before exec(), and re-init the join queue.
 * We are called by the low-level asm prologue, and will pursue our execution at
 * the end of this function.
 */
void pre_launch_proc(void) {
	tcb_t *old = current()->pcb->prev_main_thread;

	if ((old == NULL) || (current() != current()->pcb->main_thread))
		return ;

	clean_thread(old);
}

/* Copy all relevant fields of PCB */
pcb_t *duplicate_process(pcb_t *parent)
{
	pcb_t *pcb;

	/* Initialize a new PCB */
	pcb = new_process();

	pcb->page_count = parent->page_count;

	/* Affiliate the new process to the parent */
	pcb->parent = parent;

	/* Clone all file descriptors */
	if (vfs_clone_fd(parent->fd_array, pcb->fd_array)) {
		printk("!! Error while cloning fds\n");
		kernel_panic();
	}

	return pcb;
}

/*
 * For a new process from the current running process.
 */
int do_fork(void)
{
	pcb_t *newp, *parent;
	uint32_t flags;

	flags = local_irq_save();

	parent = current()->pcb;

	/* For the time being, we *only* authorize to fork() from the main thread */
	if (current() != parent->main_thread) {
		printk("%s: forking from a thread other than the main thread is not allowed so far ...\n", __func__);
		return -1;
	}

	/* Duplicate the elements of the parent process into the child */
	newp = duplicate_process(parent);

	/* Copy the user space area of the parent process */
	duplicate_user_space(parent, newp);

	/* At the moment, we spawn the main_thread only in the child. In the future, we will have to create a thread for each existing threads
	 * in the parent process.
	 */
	sprintf(newp->name, "%s_child_%d", parent->name, newp->pid);

	newp->main_thread = user_thread(NULL, newp->name, (void *) (CONFIG_KERNEL_VIRT_ADDR - PAGE_SIZE), newp);

	/* Copy the kernel stack of the main thread */
	memcpy((void *) get_kernel_stack_top(newp->main_thread->stack_slotID) - THREAD_STACK_SIZE,
	       (void *) get_kernel_stack_top(parent->main_thread->stack_slotID) - THREAD_STACK_SIZE, THREAD_STACK_SIZE);

	/*
	 * Preserve the current value of all registers concerned by this execution so that
	 * the new thread will be able to pursue its execution once scheduled.
	 */

	__save_context(newp->main_thread, get_kernel_stack_top(newp->main_thread->stack_slotID));

	local_irq_restore(flags);

	/* Return the PID of the child process. The child will do not execute this code, since
	 * it jumps to the ret_from_fork in context.S
	 */

	return newp->pid;
}

/*
 * Terminates a process.
 * All allocated resources should be released except its PCB which still contains the exit code.
 */
void do_exit(int exit_status) {
	pcb_t *pcb;
	unsigned i;

	pcb = current()->pcb;

	/* Never finish the root process */
	if (pcb->parent == NULL) {
		printk("%s: cannot finish the root process ...\n", __func__);
		kernel_panic();
	}

	local_irq_disable();

	/* Now, set the process state to zombie, before definitively die... */
	pcb->state = PROC_STATE_ZOMBIE;

	/* Set the exit code */
	pcb->exit_status = exit_status;

	/* Close the file descriptors */

	for (i = 0; i < FD_MAX; i++)
		do_close(i);

	/* Release all allocated pages for user space */
	release_proc_pages(pcb);

	/*
	 * We are finished ... Properly terminate the process main thread, which will lead to
	 * the wake up of the parent.
	 */

	thread_exit(NULL);
}

/*
 * Waitpid implementation - do_waitpid() does the following operations:
 * - Suspend the current process until the child process finished its execution (exit())
 * - Get the exit code from the child PCB
 * - Clean the PCB and page tables
 * - Return the pid if successful operation
 */
int do_waitpid(uint32_t pid, uint32_t *wstatus, uint32_t options) {
	pcb_t *child;
	uint32_t flags;

	flags = local_irq_save();

	child = find_proc_by_pid(pid);
	if (!child) {
		set_errno(ESRCH);
		return -1;
	}

	/* In the case the of NOHANG if the child did not change state,
	 * the waitpid return 0;
	 */
	if (options & WNOHANG)
		if (child->state != PROC_STATE_ZOMBIE)
			return 0;


	/* Wait on the main_thread of this process */
	thread_join(child->main_thread);

	/* Once exit'd, the child process must be in zombie state */
	ASSERT(child->state == PROC_STATE_ZOMBIE);

	/* Free the page tables used for this process */
	reset_l1pgtable(child->pgtable, true);

#warning still need to return a posix-compliant status...
	/* Get the exit code left in the PCB by the child */
	if (wstatus) 
		*wstatus = child->exit_status;
	 
	/* Finally remove the process from the system definitively */
	remove_proc(child);

	local_irq_restore(flags);

	return pid;
}


/* @brief Currently this function will only return the current position
 *		of the heap. 
 */
uint32_t do_sbrk(int increment)
{

#warning FIXME: allow increment of brk
	pcb_t *pcb = current()->pcb;

	if (!pcb) {
		/* case there is no pcb context */
		set_errno(ESRCH);
		return -1;
	}

	return pcb->heap_base;
}

/* @brief This function looks for a valid fd.
 */
int proc_register_fd(int gfd)
{
	int fd;
	pcb_t *pcb = current()->pcb;

	if (!pcb)
		return -1;

	fd = proc_new_fd(pcb);

	if (fd < 0) {
		set_errno(ENFILE);
		DBG("Number of local fd reached\n");
		return fd;
	}

	pcb->fd_array[fd] = gfd;

	return fd;
}
