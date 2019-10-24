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
 *
 * SO3 kernel memory management
 *
 */
#define DEBUG

#include <common.h>
#include <memory.h>
#include <heap.h>
#include <fdt.h>
#include <sizes.h>

#include <asm/mmu.h>
#include <asm/cacheflush.h>

#include <mach/uart.h>

#include <generated/autoconf.h>

extern unsigned long __bss_start, __bss_end;
extern unsigned long __vectors_start, __vectors_end;
mem_info_t mem_info;

/*
 * Clear the .bss section in the kernel memory layout.
 */
void clear_bss(void) {
	unsigned char *cp = (unsigned char *) &__bss_start;

	/* Zero out BSS */
	while (cp < (unsigned char *) &__bss_end)
		*cp++ = 0;
}

/*
 * Main memory init function
 */

void memory_init(void) {
#ifdef CONFIG_MMU
	int offset;
	uint32_t *new_sys_pgtable;
	page_t *vectors_page;
#endif

	/* Initialize the kernel heap */
	heap_init();

#ifdef CONFIG_MMU
	/* Set the virtual address of the real system page table */
	__sys_l1pgtable = (uint32_t *) (CONFIG_KERNEL_VIRT_ADDR + L1_SYS_PAGE_TABLE_OFFSET);

	/* Access to device tree */
	offset = get_mem_info((void *) _fdt_addr, &mem_info);
	if (offset >= 0)
		DBG("Found %d MB of RAM at 0x%08X\n", mem_info.size / SZ_1M, mem_info.phys_base);

	/* Initialize the kernel heap */
	heap_init();

	init_io_mapping();

	printk("%s: relocating the device tree from %x to %p (size of %d bytes)\n", __func__, _fdt_addr, &__end, fdt_totalsize(_fdt_addr));

	/* Move the device after the kernel stack (at &_end according to the linker script) */
	fdt_move((const void *) _fdt_addr, &__end, fdt_totalsize(_fdt_addr));
	_fdt_addr = (uint32_t) &__end;

	/* Initialize the free page list */
	frame_table_init(((uint32_t) &__end) + fdt_totalsize(_fdt_addr));

	/* Re-setup a system page table with a better granularity */
	new_sys_pgtable = new_l1pgtable();

	create_mapping(new_sys_pgtable, CONFIG_KERNEL_VIRT_ADDR, CONFIG_RAM_BASE, get_kernel_size());

	/* Mapping uart I/O for debugging purposes */
	create_mapping(new_sys_pgtable, UART_BASE, UART_BASE, PAGE_SIZE);

	/*
	 * Switch to the temporary page table in order to re-configure the original system page table
	 * Warning !! After the switch, we do not have any mapped I/O until the driver core gets initialized.
	 */

	mmu_switch(new_sys_pgtable);

	/* Re-configuring the original system page table */
	memcpy((unsigned char *) __sys_l1pgtable, (unsigned char *) new_sys_pgtable, L1_PAGETABLE_SIZE);

	/* Finally, switch back to the original location of the system page table */
	mmu_switch(__sys_l1pgtable);

	/* Finally, prepare the vector page at its correct location */
	vectors_page = get_free_page();

	create_mapping(NULL, 0xffff0000, pfn_to_phys(page_to_pfn(vectors_page)), PAGE_SIZE);

	memcpy((void *) 0xffff0000, (void *) &__vectors_start, (void *) &__vectors_end - (void *) &__vectors_start);

	set_pgtable(__sys_l1pgtable);


#endif /* CONFIG_MMU */
}

