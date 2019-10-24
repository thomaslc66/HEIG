/*-------------------------------------------------------------
 * stdlib.h
 *
 * Header file for standard library functions.
 *-------------------------------------------------------------*/

#ifndef STDLIB_H
#define STDLIB_H

#include "syscall.h"

#define true	1
#define false	0

#define EXIT_FAILURE    1       /* Failing exit status.  */
#define EXIT_SUCCESS    0       /* Successful exit status.  */

#define min(a,b)  (((a) < (b)) ? (a) : (b))
#define max(a,b)  (((a) > (b)) ? (a) : (b))

#define divRoundDown(n,s)  ((n) / (s))
#define divRoundUp(n,s)    (((n) / (s)) + ((((n) % (s)) > 0) ? 1 : 0))

int atoi(const char *s);
int abs(int n);
int log2i(int n);

/* malloc */
void *malloc(size_t size);
void free(void *ptr);

#endif /* STDLIB_H */
