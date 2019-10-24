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

#ifndef MEMORY_H
#define MEMORY_H

#include <types.h>

#include <asm/memory.h>
#include <generated/autoconf.h>

/* Transitional page used for temporary mapping */
#define TRANSITIONAL_MAPPING	0xf0000000

/* PAGE_SHIFT determines the page size */
#define PAGE_SHIFT              12
#define PAGE_SIZE               (1 << PAGE_SHIFT)
#define PAGE_MASK               (~(PAGE_SIZE-1))

struct mem_info {
    uint32_t phys_base;
    uint32_t size;
    uint32_t avail_pages; /* Available pages including frame table, without the low kernel region */
};
typedef struct mem_info mem_info_t;

extern mem_info_t mem_info;

/*
 * Frame table which is constituted by the set of struct page.
 */
struct page {
	/* If the page is not mapped yet, and hence free. */
	bool free;
};
typedef struct page page_t;

extern page_t *frame_table;

#define pfn_to_phys(pfn) ((pfn) << PAGE_SHIFT)
#define phys_to_pfn(phys) ((phys) >> PAGE_SHIFT)

#define __pa(vaddr) ((vaddr) - CONFIG_KERNEL_VIRT_ADDR + CONFIG_RAM_BASE)
#define __va(paddr) ((paddr) - CONFIG_RAM_BASE + CONFIG_KERNEL_VIRT_ADDR)

#define page_to_pfn(page) ((uint32_t) ((uint32_t) ((page)-frame_table) + phys_to_pfn(__pa((uint32_t) frame_table))))
#define pfn_to_page(pfn) (&frame_table[((pfn)-(__pa((uint32_t) frame_table) >> PAGE_SHIFT))])

void clear_bss(void);
void init_mmu(void);
void memory_init(void);

void frame_table_init(uint32_t frame_table_start);

/* Get memory informations from a device tree */
int get_mem_info(const void *fdt, mem_info_t *info);

page_t *get_free_page(void);
void release_page(page_t *page);

uint32_t get_kernel_size(void);

uint32_t *current_pgtable(void);
inline void set_pgtable(uint32_t *pgtable);


void init_io_mapping(void);
uint32_t io_map(uint32_t phys, uint32_t size);

#endif /* MEMORY_H */
