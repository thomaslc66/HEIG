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
 * - July 2017: Daniel Rossier
 *
 */

#include <sync.h>
#include <schedule.h>
#include <spinlock.h>

/*
 * Wait for completion function.
 * The critical section is managed by the spinlock of the waitqueue.
 * When the thread has to wait, IRQs are disabled to avoid race condition between
 * the call to waiting(). The IRQ
 */
void wait_for_completion(completion_t *completion) {
	queue_thread_t q_tcb;

	ASSERT(local_irq_is_enabled());

	spin_lock(&completion->wait.lock);

	q_tcb.tcb = current();

	if (!completion->count) {

		list_add_tail(&q_tcb.list, &completion->wait.tcb_list);

		do {
			local_irq_disable();

			spin_unlock(&completion->wait.lock);

			waiting();

			local_irq_enable();

			spin_lock(&completion->wait.lock);
		} while (!completion->count);
	}
	completion->count--;

	spin_unlock(&completion->wait.lock);

}

/*
 * Wake a thread waiting on a completion.
 */
void complete(completion_t *completion) {
	queue_thread_t *curr, *next;

	spin_lock(&completion->wait.lock);

	completion->count++;

	list_for_each_entry_safe(curr, next, &completion->wait.tcb_list, list) {

		ready(curr->tcb);

		list_del(&curr->list);

	}


	spin_unlock(&completion->wait.lock);

}

void init_completion(completion_t *completion) {
	INIT_LIST_HEAD(&completion->wait.tcb_list);
	spin_lock_init(&completion->wait.lock);

	completion->count = 0;
}
