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
 */

#include <driver.h>
#include <device.h>

#include <fdt.h>
#include <string.h>		/* strcmp, strncpy */
#include <linker.h>
#include <common.h>

/* Now supported only one level of sub node */
struct fdt_status {
	dev_info_t *fdt_parent[MAX_SUBNODE];
	int fdt_cur_lvl;
};

static struct fdt_status fdt_cur_status =  {
			  .fdt_parent = {NULL},
			  .fdt_cur_lvl = 0,
};


/* Initialize dev_info structure to default/invalid values */
static void init_dev_info(dev_info_t *info) {

	/* Clear out whole structure */

	memset(info, 0, sizeof(info));

	/* Initialize specific fields to default/invalid values */
	info->base = 0xFFFFFFFF;
	info->irq = -1;
	info->status = STATUS_UNKNOWN;
	info->offset_dts = -1;
	info->parent = NULL;
	info->fdt = 0;
}

/* Get memory informations from a device tree */
int get_mem_info(const void *fdt, mem_info_t *info) {
	int offset;
	const struct fdt_property *prop;
	const fdt32_t *p;

	offset = fdt_path_offset(fdt, "/memory");

	/* "memory" node not found --> error */
	if (offset < 0) {
		return offset;
	}

	prop = fdt_get_property(fdt, offset, "reg", NULL);

	if (prop) {
		
		p = (const fdt32_t *)prop->data;
				
		info->phys_base = fdt32_to_cpu(p[0]);
		info->size = fdt32_to_cpu(p[1]);
	}

	return offset;
}


int fdt_get_int(dev_info_t *dev, const char *name) {
	const struct fdt_property *prop;
	int prop_len;
	fdt32_t *p;

	prop = fdt_get_property((void *) _fdt_addr, dev->offset_dts, name, &prop_len);

	if (prop) {
		p = (fdt32_t *) prop->data;

		return fdt32_to_cpu(p[0]);
	} else
		return -1;
}

/* Get device informations/parameters from a device tree */
int get_dev_info(const void *fdt, int offset, const char *compat, dev_info_t *info) {

	int new_offset;
	const struct fdt_property *prop;
	int prop_len;
	const fdt32_t *p;
	const char *compat_str, *node_str;
	int depth = 0;

	/* Initialize dev_info structure to default/invalid values */
	init_dev_info(info);


	/* Find first compatible node in tree */
	if (strcmp(compat, "*") == 0)
		new_offset = fdt_next_node(fdt, offset, &depth);
	else
		new_offset = fdt_node_offset_by_compatible(fdt, offset, compat);


	if (new_offset < 0)
		/* No node found */
		return -1;


	if (depth > MAX_SUBNODE) {
		printk("Cannot enter subnode, 4 subnode max \n");
		BUG();
		return new_offset;
	}

	fdt_cur_status.fdt_parent[fdt_cur_status.fdt_cur_lvl] = info;

	if (!depth) {
		info->parent = NULL;
	}
	else if (depth > fdt_cur_status.fdt_cur_lvl) {
		fdt_cur_status.fdt_cur_lvl++;
	}
	else if (depth < fdt_cur_status.fdt_cur_lvl) {
		fdt_cur_status.fdt_cur_lvl--;
	}
	else {
		info->parent = fdt_cur_status.fdt_parent[fdt_cur_status.fdt_cur_lvl-1];
	}

	info->offset_dts = new_offset;
	info->fdt = (void *) fdt;

	compat_str = fdt_getprop(fdt, new_offset, "compatible", &prop_len);

	if (!compat_str) {
		return new_offset;
	}

	if (prop_len > MAX_COMPAT_SIZE) {
		DBG("Length of Compatible string > %d chars\n", MAX_COMPAT_SIZE);
		return new_offset;
	}

	strncpy(info->compatible, compat_str, prop_len);

	node_str = fdt_get_name(fdt, new_offset, &prop_len);
	if (prop_len > MAX_COMPAT_SIZE) {
	 	DBG("Length of Compatible string > %d chars\n", MAX_NODE_SIZE);
		return new_offset;
	}

	strncpy(info->nodename, node_str, prop_len);

	prop = fdt_get_property(fdt, new_offset, "status", &prop_len);

	if (prop && (strcmp(prop->data,"disabled") == 0)) {
		info->status = STATUS_DISABLED;
	} 

	prop = fdt_get_property(fdt, new_offset, "reg", &prop_len);
	
	if (prop) {
		
		p = (const fdt32_t *) prop->data;
				
			info->base = fdt32_to_cpu(p[0]);

			if (prop_len > sizeof(uint32_t)) {
				/* We have a size information */
				info->size = fdt32_to_cpu(p[1]);
			} else {
				info->size = 0;
			}
		
	} 
	
	prop = fdt_get_property(fdt, new_offset, "interrupts", &prop_len);

	if (prop) {		
		p = (const fdt32_t *) prop->data;
		
		if (prop_len == sizeof(uint32_t))
			info->irq = fdt32_to_cpu(p[0]);
		else
			/* Unsupported size of interrupts property */
			return -1;
	}

	/* We got all required information, the device is ready to be initialized */
	info->status = STATUS_INIT_PENDING;

	return new_offset;
}

