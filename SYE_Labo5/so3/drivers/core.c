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
 * - May 2017: Daniel Rossier
 *
 * Generic core driver functions
 *
 */

#if 0
#define DEBUG
#endif

#include <common.h>

#include <device.h>
#include <driver.h>

/*
 * Read the content of a device tree and associate a generic device info structure to each
 * relevant entry.
 *
 * So far, the device tree can have only one level of subnode (meaning that the root can contain only
 * nodes at the same level. Managing further sub-node levels require to adapt kernel/fdt.c
 *
 */
void init_driver_from_dtb(void) {
	unsigned int count;
	driver_entry_t *driver_entries;
	dev_info_t device_info;
	int i;
	int offset, new_off;

	count = ll_entry_count(driver_entry_t, driver);

	driver_entries = ll_entry_start(driver_entry_t, driver);

	offset = 0;

	DBG("Now scanning the device tree to retrieve all devices...\n");

	while ((new_off = get_dev_info((void *) _fdt_addr, offset, "*", &device_info)) != -1) {

		for (i = 0; i < count; i++) {

			if (strcmp(device_info.compatible, driver_entries[i].compatible) == 0) {

				DBG("Found compatible: %s\n",driver_entries[i].compatible);
				DBG("    Compatible:   %s\n", device_info.compatible);
				DBG("    Base address: 0x%08X\n", device_info.base);
				DBG("    Size:         0x%08X\n", device_info.size);
				DBG("    IRQ:          %d\n", device_info.irq);

#ifdef CONFIG_MMU
				/* Perform the mapping in the I/O virtual address space */
				device_info.base = io_map(device_info.base, device_info.size);
#endif

				driver_entries[i].init(&device_info);

				break;
			}

		}
		offset = new_off;
	}
}
