/*
 * pthread.h
 *
 *  Created on: 13 oct. 2008
 *      Author: drossier
 */

#ifndef PTHREAD_H_
#define PTHREAD_H_

#include <bits/alltypes.h>


typedef int pthread_t;

/* Thread creation */
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);

/* Thread join / synchronisation */
int pthread_join(pthread_t thread, void **value_ptr);

/* Modify thread priority */
int pthread_setschedprio(pthread_t thread, int prio);

/* Thread exit */
void pthread_exit(void *value_ptr);

#ifdef TEST_LABO03
void pthread_test_start(void);
int pthread_test_verif(void);
#endif

#endif /* PTHREAD_H_ */
