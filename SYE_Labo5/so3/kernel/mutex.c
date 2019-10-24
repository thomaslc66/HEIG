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
 *
 * Locking functions for SO3  - inspired from Linux code, however quite different
 *
 */

#include <mutex.h>
#include <schedule.h>

void mutex_lock(struct mutex *lock) {

	struct mutex_waiter waiter;

	spin_lock(&lock->wait_lock);

	/*
	 * Once more, try to acquire the lock. Only try-lock the mutex if
	 * it is unlocked to reduce unnecessary xchg() operations.
	 */
	if (!mutex_is_locked(lock) && (atomic_xchg(&lock->count, 0) == 1))
		goto skip_wait;

	if (mutex_is_locked(lock) && (lock->owner == current())) {
		lock->recursive_count++;
		goto skip_wait;
	}

	memset(&waiter, 0, sizeof(waiter));

	for (;;) {
		/*
		 * Lets try to take the lock again - this is needed even if
		 * we get here for the first time (shortly after failing to
		 * acquire the lock), to make sure that we get a wakeup once
		 * it's unlocked. Later on, if we sleep, this is the
		 * operation that gives us the lock. We xchg it to -1, so
		 * that when we release the lock, we properly wake up the
		 * other waiters. We only attempt the xchg if the count is
		 * non-negative in order to avoid unnecessary xchg operations:
		 */
		if ((atomic_read(&lock->count) >= 0) && (atomic_xchg(&lock->count, -1) == 1))
			break;

		local_irq_disable();

		/* Add waiting tasks to the end of the waitqueue (FIFO) */
		waiter.tcb = current();
		list_add_tail(&waiter.list, &lock->waitqueue);

		/* didn't get the lock, go to sleep: */
		spin_unlock(&lock->wait_lock);

		waiting();

		local_irq_enable();

		spin_lock(&lock->wait_lock);
	}

	/* set it to 0 if there are no waiters left */
	if (likely(list_empty(&lock->waitqueue)))
		atomic_set(&lock->count, 0);

	skip_wait:

	/* got the lock - cleanup and rejoice! */
	lock->owner = current();

	spin_unlock(&lock->wait_lock);

}

void mutex_unlock(struct mutex *lock) {

	struct mutex_waiter *waiter = NULL;

	spin_lock(&lock->wait_lock);

	if (lock->recursive_count) {
		lock->recursive_count--;
		spin_unlock(&lock->wait_lock);
		return ;
	}
	spin_unlock(&lock->wait_lock);

	/*
	 * As a performance measurement, release the lock before doing other
	 * wakeup related duties to follow. This allows other tasks to acquire
	 * the lock sooner, while still handling cleanups in past unlock calls.
	 * This can be done as we do not enforce strict equivalence between the
	 * mutex counter and wait_list.
	 *
	 * Some architectures leave the lock unlocked in the fastpath failure
	 * case, others need to leave it locked. In the later case we have to
	 * unlock it here - as the lock counter is currently 0 or negative.
	 */

	atomic_set(&lock->count, 1);

	spin_lock(&lock->wait_lock);

	if (!list_empty(&lock->waitqueue)) {

		/* Get the waiting the first entry of this associated waitqueue */
		waiter = list_entry(lock->waitqueue.next, struct mutex_waiter, list);

		list_del(&waiter->list);
		wake_up(waiter->tcb);

	}

	spin_unlock(&lock->wait_lock);

}

static struct mutex lock;

/*
 * The following syscall implementation are a first attempt, mainly used for debugging kernel mutexes.
 */
int do_mutex_lock(void) {
	DBG("## mutex try locking by tid %d\n", current()->tid);
	mutex_lock(&lock);

	return 0;
}

int do_mutex_unlock(void) {
	DBG("## mutex unlocking by tid %d\n", current()->tid);
	mutex_unlock(&lock);

	return 0;
}

int do_mutex_init(void) {
	mutex_init(&lock);

	return 0;
}

void mutex_init(struct mutex *lock) {

	atomic_set(&lock->count, 1);
	spin_lock_init(&lock->wait_lock);
	INIT_LIST_HEAD(&lock->waitqueue);

}




