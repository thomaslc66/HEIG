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
 * - 2015-2017: Daniel Rossier
 *
 *
 */

#include <common.h>
#include <types.h>
#include <memory.h>
#include <spinlock.h>
#include <sizes.h>
#include <process.h>

#include <asm/mmu.h>
#include <asm/cacheflush.h>

uint32_t *__sys_l1pgtable;

page_t *frame_table;
static spinlock_t ft_lock;
static uint32_t ft_pfn_end;

/* Page-aligned kernel size (including frame table) */
static uint32_t kernel_size;

/* Current available I/O range address */
uint32_t io_mapping_current;

uint32_t *__current_pgtable;

uint32_t *current_pgtable(void) {
	return __current_pgtable;
}

inline void set_pgtable(uint32_t *pgtable) {
	__current_pgtable = pgtable;
}

/* Initialize the frame table */
void frame_table_init(uint32_t frame_table_start) {
	uint32_t i, ft_phys, ft_length, ft_pages;

	/* The frame table (ft) is placed (page-aligned) right after the kernel region. */
	ft_phys = ALIGN_UP(__pa(frame_table_start), PAGE_SIZE);

	frame_table = (page_t *) __va(ft_phys);

	/* Size of the available memory (without the kernel region) */
	mem_info.avail_pages = (mem_info.size - (ft_phys - mem_info.phys_base)) >> PAGE_SHIFT;

	/* Determine the length of the frame table in bytes */
	ft_length = mem_info.avail_pages * sizeof(page_t);

	/* Keep the frame table with a page size granularity */
	ft_pages = (ALIGN_UP(ft_length, PAGE_SIZE)) >> PAGE_SHIFT;

	for (i = 0; i < ft_pages; i++)
		frame_table[i].free = false;

	for (i = ft_pages; i < mem_info.avail_pages; i++)
		frame_table[i].free = true;

	ft_pfn_end = (ft_phys >> PAGE_SHIFT) + ft_pages - 1;

	kernel_size = (ft_pfn_end << PAGE_SHIFT) - CONFIG_RAM_BASE;

	printk("SO3 Memory information:\n");

	printk("  - kernel size including frame table is: %d (%x) bytes, %d MB\n", kernel_size, kernel_size, kernel_size / SZ_1M);
	printk("  - Frame table size is: %d bytes\n", ft_length);

	spin_lock_init(&ft_lock);
}

uint32_t get_kernel_size(void) {
	return kernel_size;
}

/*
 * Get a free page. Return the pfn.
 */
page_t *get_free_page(void) {
	uint32_t i;

	spin_lock(&ft_lock);
	for (i = 0; i < mem_info.avail_pages; i++) {
		if (frame_table[i].free) {
			frame_table[i].free = false;

			spin_unlock(&ft_lock);

			/* Found an available page */
			return &frame_table[i];
		}
	}
	spin_unlock(&ft_lock);

	/* No available page */
	return NULL;
}

/*
 * Release a page, mark as free.
 */
void release_page(page_t *page) {

	spin_lock(&ft_lock);
	page->free = true;
	spin_unlock(&ft_lock);
}

/*
 * I/O address space management
 */

/* Init the I/O address space */
void init_io_mapping(void) {
	io_mapping_current = IO_MAPPING_BASE;
}

/* Map a I/O address range to its physical range */
uint32_t io_map(uint32_t phys, uint32_t size) {
	uint32_t virt_addr, offset;

	/* Make sure the virtual address will be correctly aligned (either section or page aligned). */
	io_mapping_current = ALIGN_UP(io_mapping_current, ((size < SZ_1M) ? PAGE_SIZE : SZ_1M));

	/* Preserve a possible offset */
	offset = phys & 0xfff;

	virt_addr = io_mapping_current;
	create_mapping(NULL, virt_addr, phys, size);

	io_mapping_current += size;

	return virt_addr + offset;

}

