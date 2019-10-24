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
 * - June 2017: Daniel Rossier
 */

#if 0
#define DEBUG
#endif

#include <memory.h>
#include <heap.h>
#include <sizes.h>
#include <fdt.h>

#include <asm/mmu.h>
#include <asm/cacheflush.h>

#include <mach/uart.h>

#include <generated/autoconf.h>

/* Reference to the system 1st-level page table */
static void alloc_init_pte(uint32_t *l1pte, unsigned long addr, unsigned long end, unsigned long pfn)
{
	uint32_t *l2pte;
	uint32_t size;

	if (!*l1pte) {
		size = L2_PAGETABLE_ENTRIES * sizeof(uint32_t);

		l2pte = memalign(size, SZ_1K);

		ASSERT(l2pte != NULL);
		 
		memset(l2pte, 0, size);

		*l1pte = (__pa((uint32_t) l2pte) & L1DESC_L2PT_BASE_ADDR_MASK) | L1DESC_TYPE_PT;

		DBG("Allocating a L2 page table at %p in l1pte: %p with contents: %x\n", l2pte, l1pte, *l1pte);
	}

	l2pte = l2pte_offset(l1pte, addr);

	do {
		*l2pte = (pfn << PAGE_SHIFT) | L2DESC_SMALL_PAGE_AP01 | L2DESC_SMALL_PAGE_AP2 | L2DESC_PAGE_TYPE_SMALL;
		*l2pte &= ~L1DESC_PT_DOMAIN_MASK;
		*l2pte |= PTE_DESC_DOMAIN_0;

		DBG("Setting l2pte %p with contents: %x\n", l2pte, *l2pte);

		pfn++;
	} while (l2pte++, addr += PAGE_SIZE, addr != end);


}

static void alloc_init_section(uint32_t *l1pte, uint32_t addr, uint32_t end, uint32_t phys)
{
	/*
	 * Try a section mapping - end, addr and phys must all be aligned
	 * to a section boundary.
	 */

	if (((addr | end | phys) & ~L1_SECT_MASK) == 0) {

		do {
			*l1pte = phys  | L1DESC_SECT_AP_WRITE | L1DESC_SECT_AP_READ | L1DESC_TYPE_SECT;
			*l1pte &= ~L1DESC_SECT_DOMAIN_MASK;
			*l1pte |= PTE_DESC_DOMAIN_0;

			DBG("Allocating a section at l1pte: %p content: %x\n", l1pte, *l1pte);

			phys += L1_SECT_SIZE;

		} while (l1pte++, addr += L1_SECT_SIZE, addr != end);


	} else {
		/*
		 * No need to loop; L2 pte's aren't interested in the
		 * individual L1 entries.
		 */
		alloc_init_pte(l1pte, addr, end, phys >> PAGE_SHIFT);
	}
}

/*
 * Create a static mapping between a virtual range and a physical range
 */
void create_mapping(uint32_t *l1pgtable, uint32_t virt_base, uint32_t phys_base, uint32_t size) {

	uint32_t addr, end, length, next;
	uint32_t *l1pte;

	/* If l1pgtable is NULL, we consider the system page table */
	if (l1pgtable == NULL)
		l1pgtable = __sys_l1pgtable;

	addr = virt_base & PAGE_MASK;
	length = ALIGN_UP(size + (virt_base & ~PAGE_MASK), PAGE_SIZE);

	l1pte = l1pte_offset(l1pgtable, addr);

	end = addr + length;

	do {
		next = pgd_addr_end(addr, end);

		alloc_init_section(l1pte, addr, next, phys_base);

		phys_base += next - addr;
		addr = next;

	} while (l1pte++, addr != end);

	flush_tlb_all();
}

/* Empty the corresponding l2 entries */
static void free_l2_mapping(uint32_t *l1pte, unsigned long addr, unsigned long end) {
	uint32_t *l2pte;
	int i;
	bool found;

	l2pte = l2pte_offset(l1pte, addr);

	do {
		DBG("Re-setting l2pte to 0: %p\n", l2pte);

		*l2pte = 0; /* Free this entry */

	} while (l2pte++, addr += PAGE_SIZE, addr != end);

	for (i = 0, found = false, l2pte = l2pte_first(l1pte); !found && (i < L2_PAGETABLE_ENTRIES); i++)
		found = (*(l2pte + i) != 0);


	if (!found) {
		DBG("Freeing allocated L2 page table: %p\n", l2pte);

		free(l2pte); /* Remove the L2 page table since all no entry is mapped */

		DBG("Re-setting l1pte %p t0 0\n", l1pte);
		*l1pte = 0; /* Free the L1 entry as well */
	}
}

/* Empty the corresponding l1 entries */
static void free_l1_mapping(uint32_t *l1pte, uint32_t addr, uint32_t end) {

	/*
	 * Try a section mapping - end, addr and phys must all be aligned
	 * to a section boundary.
	 */
	if (((addr | end) & ~L1_SECT_MASK) == 0) {

		do {
			DBG("Re-setting l1pte: %p to 0\n", l1pte);

			*l1pte = 0; /* Free this entry */

		} while (l1pte++, addr += L1_SECT_SIZE, addr != end);

	} else {
		/*
		 * No need to loop; L2 pte's aren't interested in the
		 * individual L1 entries.
		 */
		free_l2_mapping(l1pte, addr, end);
	}
}

/*
 * Release an existing mapping
 */
void release_mapping(uint32_t *pgtable, uint32_t virt_base, uint32_t size) {
	uint32_t addr, end, length, next;
	uint32_t *l1pte;

	addr = virt_base & PAGE_MASK;
	length = ALIGN_UP(size + (virt_base & ~PAGE_MASK), PAGE_SIZE);

	l1pte = l1pte_offset(pgtable, addr);

	end = addr + length;

	do {
		next = pgd_addr_end(addr, end);

		free_l1_mapping(l1pte, addr, next);

		addr = next;

	} while (l1pte++, addr != end);

	flush_tlb_all();
}

/*
 * Initial configuration of system page table
 */
void configure_l1pgtable(uint32_t l1pgtable, uint32_t fdt_addr) {
  unsigned int i;
  uint32_t *__pgtable = (uint32_t *) l1pgtable;

  /* Empty the page table */
  for (i = 0; i < 4096; i++)
	  __pgtable[i] = 0;

  /* Create an identity mapping of 1 MB on running kernel so that the kernel code can go ahead right after the MMU on */
  __pgtable[CONFIG_RAM_BASE >> L1_PAGETABLE_SHIFT] = CONFIG_RAM_BASE  | L1DESC_SECT_AP_WRITE | L1DESC_SECT_AP_READ | L1DESC_TYPE_SECT;

  /* Now, create a virtual mapping in the kernel space */
  for (i = 0; i < 6; i++)
	  __pgtable[(CONFIG_KERNEL_VIRT_ADDR >> L1_PAGETABLE_SHIFT) + i] = (((CONFIG_RAM_BASE >> L1_PAGETABLE_SHIFT) + i) << L1_PAGETABLE_SHIFT) | L1DESC_SECT_AP_WRITE | L1DESC_SECT_AP_READ | L1DESC_TYPE_SECT;

  /* At the moment, we keep a virtual mapping on the device tree - _fdt_addr contains the physical address. */
  __pgtable[fdt_addr >> L1_PAGETABLE_SHIFT] = (fdt_addr & L1_SECT_MASK) | L1DESC_SECT_AP_WRITE | L1DESC_SECT_AP_READ | L1DESC_TYPE_SECT;

  /* Early mapping I/O for UART */

  __pgtable[UART_BASE >> L1_PAGETABLE_SHIFT] = (UART_BASE & L1_SECT_MASK) | L1DESC_SECT_AP_WRITE | L1DESC_SECT_AP_READ | L1DESC_TYPE_SECT;

}

/*
 * Allocate a new L1 page table. Return NULL if it fails.
 * The page table must be 16-KB aligned.
 */
uint32_t *new_l1pgtable(void) {
	uint32_t *pgtable;

	pgtable = memalign(L1_PAGETABLE_SIZE, SZ_16K);
	if (!pgtable) {
		printk("%s: heap overflow...\n", __func__);
		kernel_panic();
	}

	/* Empty the page table */
	memset(pgtable, 0, L1_PAGETABLE_SIZE);

	return pgtable;
}

/*
 * Free a L1 page table and associated L2 page tables used for the user space area.
 * We do not consider any shared pages/page tables.
 * @remove indicate if the page tables (L1 & L2) must be erased.
 */
void reset_l1pgtable(uint32_t *l1pgtable, bool remove) {
	int i;
	uint32_t *l1pte, *l2pte;

	for (i = 0; i < (CONFIG_KERNEL_VIRT_ADDR >> L1_PAGETABLE_SHIFT); i++) {

		l1pte = l1pgtable + i;

		/* Check if a L2 page table is used */
		if (*l1pte) {
			if ((*l1pte & L1DESC_TYPE_MASK) == L1DESC_TYPE_PT) {
				l2pte = (uint32_t *) __va(*l1pte & L1DESC_L2PT_BASE_ADDR_MASK);

				free(l2pte);
			}
			*l1pte = 0;

		}
	}

	/* And finally, restore the heap memory allocated for this page table */
	if (remove)
		free(l1pgtable);

	flush_tlb_all();
}


/*
 * Switch the MMU to a L1 page table
 */
void mmu_switch(uint32_t *l1pgtable) {
	__mmu_switch(__pa((uint32_t) l1pgtable));

	flush_tlb_all();
	cache_clean_flush();
}

/* Duplicate the kernel area by doing a copy of L1 PTEs from the system page table */
void pgtable_copy_kernel_area(uint32_t *l1pgtable) {
	int i1;

	for (i1 = CONFIG_KERNEL_VIRT_ADDR >> L1_PAGETABLE_SHIFT; i1 < L1_PAGETABLE_ENTRIES; i1++)
		l1pgtable[i1] = __sys_l1pgtable[i1];
}

/*
 * Duplicate the user space memory from a memory context to another.
 * The L1 and subsequent L2 page tables are duplicated accordingly.
 *
 * The user space has only small (4 KB) pages.
 *
 * @from is the process containing the L1 page table to be duplicated
 * @to is the process containing the (already allocated) L1 page table of the target memory context
 */

void duplicate_user_space(pcb_t *from, pcb_t *to) {
	int i, j;
	uint32_t l2pgtable_size;
	uint32_t *l1pte, *l2pte;
	uint32_t *l1pte_dst, *l2pte_dst;
	page_t *page;

	l2pgtable_size = L2_PAGETABLE_ENTRIES * sizeof(uint32_t);

	for (i = 0; i < (CONFIG_KERNEL_VIRT_ADDR >> L1_PAGETABLE_SHIFT); i++) {
		l1pte = from->pgtable + i;

		if (*l1pte) {
			BUG_ON((*l1pte & L1DESC_TYPE_MASK) != L1DESC_TYPE_PT);

			l1pte_dst = to->pgtable + i;

			/* Allocate a new L2 page table for the copy */
			l2pte_dst = memalign(l2pgtable_size, SZ_1K);

			ASSERT(l2pte_dst != NULL);

			memset(l2pte_dst, 0, l2pgtable_size);

			*l1pte_dst = (__pa((uint32_t) l2pte_dst) & L1DESC_L2PT_BASE_ADDR_MASK) | L1DESC_TYPE_PT;

			for (j = 0; j < 256; j++) {
				l2pte = ((uint32_t *) __va(*l1pte & L1DESC_L2PT_BASE_ADDR_MASK)) + j;
				if (*l2pte)  {

					l2pte_dst = ((uint32_t *) __va(*l1pte_dst & L1DESC_L2PT_BASE_ADDR_MASK)) + j;

					/* Get a new free page */
					page = get_free_page();

					/* Add the new page to the process list */
					add_page_to_proc(to, page);
 
					create_mapping(current_pgtable(), TRANSITIONAL_MAPPING, pfn_to_phys(page_to_pfn(page)), PAGE_SIZE);

					/* Copy the contents */
					memcpy((void *) TRANSITIONAL_MAPPING, (void *) ((i << L1_PAGETABLE_SHIFT) | (j << L2_PAGETABLE_SHIFT)), PAGE_SIZE);

					release_mapping(current_pgtable(), TRANSITIONAL_MAPPING, PAGE_SIZE);

					*l2pte_dst = pfn_to_phys(page_to_pfn(page)) | L2DESC_SMALL_PAGE_AP01 | L2DESC_SMALL_PAGE_AP2 | L2DESC_PAGE_TYPE_SMALL;

					*l2pte_dst &= ~L1DESC_PT_DOMAIN_MASK;
					*l2pte_dst |= PTE_DESC_DOMAIN_0;
				}
			}
		}
	}
	cache_clean_flush();

}



void dump_pgtable(uint32_t *l1pgtable) {

	int i, j;
	uint32_t *l1pte, *l2pte;

	printk("           ***** Page table dump *****\n");

	for (i = 0; i < L1_PAGETABLE_ENTRIES; i++) {
		l1pte = l1pgtable + i;
		if (*l1pte) {
			if ((*l1pte & L1DESC_TYPE_MASK) == L1DESC_TYPE_SECT)
				printk(" - L1 pte@%p (idx %d) mapping %x is section type  content: %x\n", l1pgtable+i, i, i << L1_PAGETABLE_SHIFT, *l1pte);
			else
				printk(" - L1 pte@%p (idx %d) is coarse type   content: %x\n", l1pgtable+i, i, *l1pte);

			if ((*l1pte & L1DESC_TYPE_MASK) == L1DESC_TYPE_PT) {
				for (j = 0; j < 256; j++) {
					l2pte = ((uint32_t *) __va(*l1pte & L1DESC_L2PT_BASE_ADDR_MASK)) + j;
					if (*l2pte)
						printk("      - L2 pte@%p (i2=%x) mapping %x  content: %x\n", l2pte, j, (i << 20) | (j << 12), *l2pte);
				}
			}
		}
	}
}
