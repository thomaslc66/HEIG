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
 * - 2014-2017: Daniel Rossier
 */

#if 0
#define DEBUG
#endif

#include <compiler.h>
#include <schedule.h>
#include <process.h>
#include <thread.h>
#include <heap.h>
#include <softirq.h>
#include <mutex.h>

#include <asm/hardware/timer.h>
#include <asm/hardware/irq.h>
#include <asm/mmu.h>

static struct list_head readyThreads;
static struct list_head zombieThreads;

/* Global list of process */
struct list_head proc_list;
struct tcb *tcb_idle;

static tcb_t *current_thread;

u64 jiffies = 0ull;
u64 jiffies_ref = 0ull;

/*
 * The following code (normally disabled) is used for debugging purposes...
 */
#if 0
inline bool check_consistency_ready(void) {
	queue_thread_t *cur;
	tcb_t *_tcb;
	struct list_head *pos;

	list_for_each(pos, &readyThreads)
	{
		cur = list_entry(pos, queue_thread_t, list);
		_tcb = cur->tcb;
		if (_tcb->state != THREAD_STATE_READY) {
			printk("### ERROR %d on tid %d with state: %s ###\n", __LINE__, _tcb->tid, print_state(_tcb));
			return false;
		}
	}
	return true;
}
#endif /* 0 */

tcb_t *current(void) {
	return current_thread;
}

inline void set_current(struct tcb *tcb) {
	current_thread = tcb;
}

/*
 * Insert a new thread in the ready list.
 */
void ready(tcb_t *tcb) {
	uint32_t flags;
	queue_thread_t *cur;

	flags = local_irq_save();

	tcb->state = THREAD_STATE_READY;

	cur = (queue_thread_t *) malloc(sizeof(queue_thread_t));
	BUG_ON(cur == NULL);

	cur->tcb = tcb;

	/* Insert the thread at the end of the list */
	list_add_tail(&cur->list, &readyThreads);

	local_irq_restore(flags);
}

/*
 * Put a thread in the waiting state and invoke the scheduler.
 * It is assumed that the caller manages the waiting queue.
 */
void waiting(void) {
	uint32_t flags;

	flags = local_irq_save();

	ASSERT(current()->state == THREAD_STATE_RUNNING);

	current()->state = THREAD_STATE_WAITING;

	schedule();

	local_irq_restore(flags);
}

/*
 * Put a thread into the zombie queue.
 */
void zombie(void) {
	queue_thread_t *cur;
	uint32_t flags;

	ASSERT(current()->state == THREAD_STATE_RUNNING);

	flags = local_irq_save();

	current()->state = THREAD_STATE_ZOMBIE;

	cur = (queue_thread_t *) malloc(sizeof(queue_thread_t));
	BUG_ON(cur == NULL);

	cur->tcb = current();

	/* Insert the thread at the end of the list */
	list_add_tail(&cur->list, &zombieThreads);

	local_irq_restore(flags);

	schedule();
}

/*
 * Remove a thread from the zombie list.
 */
void remove_zombie(struct tcb *tcb) {
	queue_thread_t *cur;
	tcb_t *_tcb;
	struct list_head *pos, *q;

	local_irq_disable();

	ASSERT(tcb != NULL);
	ASSERT(tcb->state == THREAD_STATE_ZOMBIE);

	list_for_each_safe(pos, q, &zombieThreads)
	{
		cur = list_entry(pos, queue_thread_t, list);

		_tcb = cur->tcb;

		if (tcb == _tcb) {
			list_del(pos);

			free(cur);
			return ;
		}

	}

	printk("%s: zombie thread %d not found.\n", __func__, tcb->tid);

	BUG();
}

/*
 * Wake up a thread which is in waiting state.
 * If the thread passed as argument is not sleeping, we just call schedule().
 */
void wake_up(struct tcb *tcb) {

	ready(tcb);
	schedule();
}

/*
 * Remove a tcb from the ready list
 */
void remove_ready(struct tcb *tcb) {

	queue_thread_t *cur;
	tcb_t *_tcb;
	struct list_head *pos, *q;

	ASSERT(!local_irq_is_enabled());
	ASSERT(tcb != NULL);

	ASSERT(tcb->state == THREAD_STATE_READY);

	list_for_each_safe(pos, q, &readyThreads)
	{
		cur = list_entry(pos, queue_thread_t, list);
		_tcb = cur->tcb;

		if (tcb == _tcb) {
			list_del(pos);

			free(cur);
			return ;
		}

	}

	printk("%s: ready thread %d not found.\n", __func__, tcb->tid);

	BUG();
}


/*
 * Pick up the next ready thread to be scheduled according
 * to the scheduling policy.
 * IRQs are off.
 */
static tcb_t *next_thread(void) {
	tcb_t *tcb;
	queue_thread_t *entry;

	ASSERT(!local_irq_is_enabled());

	if (!list_empty(&readyThreads)) {
		entry = list_entry(readyThreads.next, queue_thread_t, list);

		/* Warning ! entry will be freed in remove_ready() */
		tcb = entry->tcb;
		remove_ready(tcb);

		return tcb;
	}

	return NULL;
}

/*
 * Main scheduling function.
 */
void schedule(void) {

	tcb_t *prev, *next;
	uint32_t flags;

	flags = local_irq_save();

	/* Scheduling policy: at the moment start the first ready thread */
	
	prev = current();
	next = next_thread();

	if (unlikely(next == NULL))
		next = tcb_idle;

	if ((next != NULL) && (next != prev)) {
		DBG("Now scheduling thread ID: %d name: %s\n", next->tid, next->name);

		/*
		 * The current threads (here prev) can be in different states, not only running; it may be in *waiting* or *zombie*
		 * depending on the thread activities. Hence, we put it in the ready state ONLY if the thread is in *running*.
		 */
		if ((prev != NULL) && (prev->state == THREAD_STATE_RUNNING) && (likely(prev != tcb_idle)))
			ready(prev);

		next->state = THREAD_STATE_RUNNING;
		set_current(next);

#ifdef CONFIG_MMU
		if ((next->pcb != NULL) && (next->pcb->pgtable != current_pgtable())) {
			mmu_switch(next->pcb->pgtable);
                        set_pgtable(next->pcb->pgtable);

                }
#endif /* CONFIG_MMU */


		__switch_context(prev, next);
	}


	local_irq_restore(flags);
}

/*
 * Dump the ready threads
 */
void dump_ready(void) {
	struct list_head *pos;
	queue_thread_t *cur;

	printk("Dumping the ready-threads queue: \n");

	if (list_empty(&readyThreads)) {
		printk("  <empty>\n");
		return ;
	}

	list_for_each(pos, &readyThreads)
	{
		cur = list_entry(pos, queue_thread_t, list);
		printk("  Thread ID: %d name: %s state: %d\n", cur->tcb->tid, cur->tcb->name, cur->tcb->state);

	}

}

/*
 * Dump the zombie threads
 */
void dump_zombie(void) {
	struct list_head *pos;
	queue_thread_t *cur;

	printk("Dumping the zombie-threads queue: \n");

	if (list_empty(&zombieThreads)) {
		printk("  <empty>\n");
		return ;
	}

	list_for_each(pos, &zombieThreads)
	{
		cur = list_entry(pos, queue_thread_t, list);
		printk("  Proc ID: %d Thread ID: %d state: %d\n", ((cur->tcb->pcb != NULL) ? cur->tcb->pcb->pid : 0), cur->tcb->tid, cur->tcb->state);

	}

}

/*
 * Dump information of the scheduling waitqueues.
 */
void dump_sched(void) {
	dump_ready();
	dump_zombie();
}

/*
 * Dump the list of all process threads
 */
void dump_threads(void) {
	pcb_t *pcb;
	struct tcb *tcb;
	struct list_head *p1, *p2;

	printk("Dumping all process thread state: \n");
	list_for_each(p1, &proc_list)
	{
		pcb = list_entry(p1, pcb_t, list);

		printk("  Proc ID: %d / *Main* thread ID: %d state: %s\n", pcb->pid, pcb->main_thread->tid, print_state(pcb->main_thread));
		list_for_each(p2, &pcb->threads)
		{
			tcb = list_entry(p2, tcb_t, list);

			printk("        Proc ID: %d Thread ID: %d state: %s\n", pcb->pid, tcb->tid, print_state(tcb));
		}
	}
}


void scheduler_init(void) {

	threads_init();

	INIT_LIST_HEAD(&readyThreads);
	INIT_LIST_HEAD(&zombieThreads);


	INIT_LIST_HEAD(&proc_list);

	timer_start_periodic(1000 / HZ);

	register_softirq(SCHEDULE_SOFTIRQ, schedule);

	set_current(NULL);

}
