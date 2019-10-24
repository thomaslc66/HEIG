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

#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>
#include <sizes.h>

#if 0
#define TRACKING
#endif

#define HEAP_SIZE 	(SZ_1M)

/* there's a list for each size. The size changes over the process lifetime. */
struct mem_chunk {

    /* Pointer to the next memchunk of a different size */
    struct mem_chunk *next_list;

    /* Pointer to the next memchunk of this size. */
    struct mem_chunk *next_chunk;

    /* Refer to the head of the (2nd-dimension) list for this size */
    struct mem_chunk *head;

    size_t size; /* size in bytes of the user area (this does NOT include the size of mem_chunk) */

    /* Used in case of specific alignment on address - These bytes are lost */
    size_t padding_bytes;
};
typedef struct mem_chunk mem_chunk_t;


#ifndef TRACKING
void *malloc(size_t size);
void *memalign(size_t size, unsigned int alignment);
#else
void *malloc_log(size_t size, const char *filename, const char *fname, const int line);
void *memalign_log(size_t size, unsigned int alignment, const char *filename, const char *fname, const int line);

#define malloc(x) malloc_log(x, __FILE__, __func__, __LINE__)
#define memalign(x,y) memalign_log(x, y, __FILE__, __func__, __LINE__)

#endif

void free(void *ptr);
void printHeap(void);

void heap_init(void);
void dump_heap(const char *info);


#endif /* HEAP_H */
