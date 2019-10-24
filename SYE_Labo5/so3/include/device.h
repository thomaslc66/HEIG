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
 * - <month> 2017: <first_name> <last_name>
 */


/*
 * Copyright (c) 2014, 2015, 2016, 2017 REDS Institute, HEIG-VD
 * Copyright (c) 2016, 2017 Sootech SA
 *
 * Contributors:
 * - Daniel Rossier (2015-2017)
 *
 * This file contains some piece of code for various tests in SO3.
 */

#ifndef DEVICE_H
#define DEVICE_H

#include <fdt.h>

typedef enum {
	STATUS_UNKNOWN,		/**/
	STATUS_DISABLED,
	STATUS_INIT_PENDING,
	STATUS_INITIALIZED,
} dev_status_t;

struct dev_info {
	char compatible[MAX_COMPAT_SIZE];
	char nodename[MAX_NODE_SIZE];
	uint32_t base;
	uint32_t size;
	int irq;
	dev_status_t status;
	int offset_dts;
	struct dev_info *parent;
	void *fdt;
};
typedef struct dev_info dev_info_t;

/* Get device informations from a device tree
 * This function will be in charge of allocating dev_inf struct;
 */
int get_dev_info(const void *fdt, int offset, const char *compat, dev_info_t *info);
int fdt_get_int(dev_info_t *dev, const char *name);


#endif /* DEVICE_H */
