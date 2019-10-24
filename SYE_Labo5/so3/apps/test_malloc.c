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
 * - November 2016: Xavier Ruppen>
 */

#include <common.h>
#include <heap.h>

enum test_t {
        SAME_MALLOC,
        DIFFERENT_MALLOC,
        MIXED_MALLOC,
        SIMPLE_FREE,
        SEVERAL_FREE,
        MIXED_MALLOC_FREE,
        SIMPLE_MERGE,
        DOUBLE_MERGE,
        NO_SPACE_LEFT,
        REPORTED_BUG,
        TEST_COUNT,
	MEMALIGN
};


extern void dump_heap(const char *info);

void allocate(int size, void **ptr)
{
    printk("malloc(%d): ", size);
    *ptr = malloc(size);
    if (!*ptr) {
        printk("returned NULL\n");
    }
    printk("returned %p\n", *ptr);
}

void liberate(void *ptr)
{
    printk("free(%p)\n", ptr);
    free(ptr);
}

int malloc_test(int test_no)
{
    void *ptr[100];


    printk("Test #%d\n", test_no);

    switch (test_no) {
        case SAME_MALLOC:
            allocate(100, &ptr[1]);
            dump_heap(__func__);
            printk("\n");
            allocate(100, &ptr[2]);
            dump_heap(__func__);
            printk("\n");
            allocate(100, &ptr[3]);
            dump_heap(__func__);
            printk("\n");
            allocate(100, &ptr[4]);
            dump_heap(__func__);
            printk("\n");
            break;

        case DIFFERENT_MALLOC:
            allocate(1000, &ptr[1]);
            dump_heap(__func__);
            printk("\n");
            allocate(2000, &ptr[2]);
            dump_heap(__func__);
            printk("\n");
            allocate(1300, &ptr[3]);
            dump_heap(__func__);
            printk("\n");
            allocate(100, &ptr[4]);
            dump_heap(__func__);
            printk("\n");
            break;

        case MIXED_MALLOC:
            allocate(1000, &ptr[1]);
            dump_heap(__func__);
            printk("\n");
            allocate(2000, &ptr[2]);
            dump_heap(__func__);
            printk("\n");
            allocate(100, &ptr[3]);
            dump_heap(__func__);
            printk("\n");
            allocate(1300, &ptr[4]);
            dump_heap(__func__);
            printk("\n");
            allocate(1000, &ptr[5]);
            dump_heap(__func__);
            printk("\n");
            allocate(100, &ptr[6]);
            dump_heap(__func__);
            printk("\n");
            break;

        case SIMPLE_FREE:
            allocate(100, &ptr[0]);
            dump_heap(__func__);
            printk("\n");

            liberate(ptr[0]);
            dump_heap(__func__);
            printk("\n");
            break; 

        case SEVERAL_FREE:
            allocate(1000, &ptr[1]);
            dump_heap(__func__);
            printk("\n");
            allocate(2000, &ptr[2]);
            dump_heap(__func__);
            printk("\n");
            allocate(1300, &ptr[3]);
            dump_heap(__func__);
            printk("\n");
            allocate(100, &ptr[4]);
            dump_heap(__func__);
            printk("\n");

            liberate(ptr[1]);
            dump_heap(__func__);
            printk("\n");
            liberate(ptr[2]);
            dump_heap(__func__);
            printk("\n");
            liberate(ptr[3]);
            dump_heap(__func__);
            printk("\n");
            liberate(ptr[4]);
            dump_heap(__func__);
            printk("\n");
            break;

        case MIXED_MALLOC_FREE:
            allocate(100, &ptr[1]);
            dump_heap(__func__);
            printk("\n");
            allocate(200, &ptr[2]);
            dump_heap(__func__);
            printk("\n");

            liberate(ptr[1]);
            dump_heap(__func__);
            printk("\n");

            allocate(300, &ptr[3]);
            dump_heap(__func__);
            printk("\n");

            liberate(ptr[2]);
            dump_heap(__func__);
            printk("\n");
            liberate(ptr[3]);
            dump_heap(__func__);
            printk("\n");
            break;

        case SIMPLE_MERGE:
            allocate(100, &ptr[1]);
            dump_heap(__func__);
            printk("\n");
            allocate(100, &ptr[2]);
            dump_heap(__func__);
            printk("\n");
            allocate(100, &ptr[3]);
            dump_heap(__func__);
            printk("\n");
            allocate(100, &ptr[4]);
            dump_heap(__func__);
            printk("\n");

            liberate(ptr[1]);
            dump_heap(__func__);
            printk("\n");
            liberate(ptr[2]);
            dump_heap(__func__);
            printk("\n");
            liberate(ptr[3]);
            dump_heap(__func__);
            printk("\n");
            liberate(ptr[4]);
            dump_heap(__func__);
            printk("\n");
            break;

        case DOUBLE_MERGE:
            allocate(100, &ptr[1]);
            dump_heap(__func__);
            printk("\n");
            allocate(100, &ptr[2]);
            dump_heap(__func__);
            printk("\n");
            allocate(100, &ptr[3]);
            dump_heap(__func__);
            printk("\n");
            allocate(100, &ptr[4]);
            dump_heap(__func__);
            printk("\n");

            liberate(ptr[1]);
            dump_heap(__func__);
            printk("\n");
            liberate(ptr[3]);
            dump_heap(__func__);
            printk("\n");
            liberate(ptr[2]);
            dump_heap(__func__);
            printk("\n");
            liberate(ptr[4]);
            dump_heap(__func__);
            printk("\n");
            break;

        case NO_SPACE_LEFT:
            allocate(1000, &ptr[1]);
            dump_heap(__func__);
            printk("\n");
            allocate(1000, &ptr[2]);
            dump_heap(__func__);
            printk("\n");
            allocate(1000, &ptr[3]);
            dump_heap(__func__);
            printk("\n");
            allocate(1000, &ptr[4]);
            dump_heap(__func__);
            printk("\n");
            allocate(1000, &ptr[5]);
            dump_heap(__func__);
            printk("\n");
            allocate(1000, &ptr[6]);
            dump_heap(__func__);
            printk("\n");
            allocate(1000, &ptr[7]);
            dump_heap(__func__);
            printk("\n");
            allocate(1000, &ptr[8]);
            dump_heap(__func__);
            printk("\n");
            allocate(1000, &ptr[9]);
            dump_heap(__func__);
            printk("\n");
            allocate(1000, &ptr[10]);
            dump_heap(__func__);
            printk("\n");
            break;

        case REPORTED_BUG:
            allocate(50, &ptr[0]);
            dump_heap(__func__);
            printk("\n");
            allocate(200, &ptr[1]);
            dump_heap(__func__);
            printk("\n");

            liberate(ptr[0]);
            dump_heap(__func__);
            printk("\n");
         
            allocate(500, &ptr[2]);
            dump_heap(__func__);
            printk("\n");

            liberate(ptr[1]);
            dump_heap(__func__);
            printk("\n");
            liberate(ptr[2]);
            dump_heap(__func__);
            printk("\n");
            break;

        case MEMALIGN:
        {
        	void *ptr[400], *ptr2[400];
        	int i;

        	dump_heap("before");
        	for (i = 0; i < 400; i++) {
        		ptr[i] = memalign(15, SZ_1K);
        		ptr2[i] = malloc(12);
        	}

        	for (i = 0; i < 400; i++) {
        	        free(ptr[i]);
        	        free(ptr2[i]);
        	}
        	dump_heap("after");

        	break;
        }

        default:
            break;
    }

    return 0;
}
