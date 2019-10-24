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

#ifndef MUTEX_H
#define MUTEX_H

#include <list.h>
#include <asm/atomic.h>
#include <spinlock.h>
#include <thread.h>

 struct mutex {
   /* 1: unlocked, 0: locked, negative: locked, possible waiters */
   atomic_t                count;
   tcb_t		   *owner;
   spinlock_t              wait_lock;

   /* Allow to manage recursive locking */
   uint32_t 		   recursive_count;

   struct list_head        waitqueue;
};
typedef struct mutex mutex_t;

 /*
  * List of waiters on a specific lock. This is an entry of the mutex waitqueue.
  */
struct mutex_waiter {
  struct list_head list;
  tcb_t *tcb;
};

 /**
  * mutex_is_locked - is the mutex locked
  * @lock: the mutex to be queried
  *
  * Returns 1 if the mutex is locked, 0 if unlocked.
  */
 static inline int mutex_is_locked(struct mutex *lock)
 {
 	return atomic_read(&lock->count) != 1;
 }

void mutex_lock(struct mutex *lock);
void mutex_unlock(struct mutex *lock);
void mutex_init(struct mutex *lock);

int do_mutex_init(void);
int do_mutex_lock(void);
int do_mutex_unlock(void);

#endif /* MUTEX_H */

