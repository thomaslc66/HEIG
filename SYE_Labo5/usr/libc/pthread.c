
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
 *
 * Contributors:
 *
 * - April-May 2017: Xavier Ruppen, Daniel Rossier
 *
 */

#include <pthread.h>
#include <syscall.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>

void *(*__thread_fn)(void *) = NULL;

void *__thread_routine(void *args) {
	void *(*____thread_fn)(void *);

	____thread_fn = __thread_fn;
	__thread_fn = NULL;

	____thread_fn(args);

	thread_exit(NULL);

	/* We should never be here ... */

	assert(0);

	return NULL;
}

/* Thread creation */
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg) {
	int ret;

	while (__thread_fn != NULL) ;

	__thread_fn = start_routine;
	ret = thread_create(thread, attr, __thread_routine, arg);

	return ret;
}

/* Thread join / synchronisation */
int pthread_join(pthread_t thread, void **value_ptr) {

  return thread_join(thread, value_ptr);
}

/* Modify thread priority */
int pthread_setschedprio(pthread_t thread, int prio) {
	return sched_setparam(thread, prio);
}

/* Thread exit */
void pthread_exit(void *value_ptr) {
	thread_exit(value_ptr);
}

void pthread_mutex_lock(void) {
	mutex_lock();
}

void pthread_mutex_unlock(void) {
	mutex_unlock();
}
