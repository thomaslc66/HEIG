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

#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <list.h>
#include <thread.h>

#define HZ      100


extern u64 jiffies;
extern u64 jiffies_ref;

struct tcb;

extern struct tcb *tcb_idle;

void scheduler_init(void);
void schedule(void);
void yield(void);

void ready(struct tcb *tcb);
void waiting(void);
struct tcb *pick_waiting_thread(struct tcb *tcb);
void zombie(void);

void remove_zombie(struct tcb *tcb);

void wake_up(struct tcb *tcb);

void dump_sched(void);
void dump_threads(void);

inline void set_current(struct tcb *tcb);
struct tcb *current(void);

void remove_ready(struct tcb *tcb);

typedef struct queue_thread {
	struct list_head list;
	struct tcb *tcb;
} queue_thread_t;

#endif /* SCHEDULE_H */
