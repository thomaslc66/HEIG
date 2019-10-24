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
 * - Daniel Rossier (2015-2017)
 *
 */

#ifndef MMU_H
#define MMU_H

#define L1_SYS_PAGE_TABLE_OFFSET	0x4000

/* Define the number of entries in each page table */

#define L1_PAGETABLE_ORDER      	12
#define L2_PAGETABLE_ORDER      	8

#define L1_PAGETABLE_ENTRIES    	(1 << L1_PAGETABLE_ORDER)
#define L2_PAGETABLE_ENTRIES    	(1 << L2_PAGETABLE_ORDER)

#define L1_PAGETABLE_SHIFT      	20
#define L2_PAGETABLE_SHIFT      	12

#define L1_PAGETABLE_SIZE       	(PAGE_SIZE << 2)

/* To get the address of the L2 page table from a L1 descriptor */
#define L1DESC_L2PT_BASE_ADDR_SHIFT	10
#define L1DESC_L2PT_BASE_ADDR_OFFSET	(1 << L1DESC_L2PT_BASE_ADDR_SHIFT)
#define L1DESC_L2PT_BASE_ADDR_MASK	(~(L1DESC_L2PT_BASE_ADDR_OFFSET - 1))

/* Page table type */

#define L1_MAP_SIZE			(1UL << L1_PAGETABLE_SHIFT)
#define L1_MAP_MASK			(~(L1_MAP_SIZE - 1))

#define L1_SECT_SIZE			(0x100000)
#define L1_SECT_MASK            	(~(L1_SECT_SIZE - 1))

#define L1DESC_SECT_BUFFERABLE     	(1 << 2)
#define L1DESC_SECT_CACHEABLE      	(1 << 3)
#define L1DESC_SECT_XN             	(1 << 4)

#define L1DESC_SECT_DOMAIN_MASK       	(0xf << 5)
#define L1DESC_PT_DOMAIN_MASK       	(0xf << 5)

#define PTE_DESC_DOMAIN_0		(0x0 << 5)

#define L1DESC_SECT_AP_WRITE      	(1 << 10)
#define L1DESC_SECT_AP_READ        	(1 << 11)

#define L1DESC_TYPE_MASK		0x3
#define L1DESC_TYPE_SECT 		0x2
#define L1DESC_TYPE_PT 	        	0x1

/* L2 page table attributes */
#define L2DESC_SMALL_PAGE_ADDR_MASK	(~(PAGE_SIZE-1))

/* AP[0] is used as Access Flag.
 * Access Flag (AF): ARMv8.0 requires that software manages the Access flag. This means an Access flag fault is generated whenever
 * an attempt is made to read into the TLB a translation table descriptor entry for which the value of the Access flag
 * is 0.
 * AP[1] and AP[2] are set to 1 for read/write at any privilege.
 */
#define L2DESC_SMALL_PAGE_AP01		(0x3 << 4)
#define L2DESC_SMALL_PAGE_AP2		(1 << 9)
#define L2DESC_PAGE_TYPE_SMALL		0x2

/* Given a virtual address, get an entry offset into a page table. */
#define l1pte_index(a) ((((uint32_t) a) >> L1_PAGETABLE_SHIFT) & (L1_PAGETABLE_ENTRIES - 1))
#define l2pte_index(a) ((((uint32_t) a) >> L2_PAGETABLE_SHIFT) & (L2_PAGETABLE_ENTRIES - 1))

#define l1pte_offset(pgtable, addr)     (pgtable + l1pte_index(addr))
#define l2pte_offset(l1pte, addr) 	(((uint32_t *) (__va(*l1pte) & L1DESC_L2PT_BASE_ADDR_MASK)) + l2pte_index(addr))
#define l2pte_first(l1pte)		(((uint32_t *) (__va(*l1pte) & L1DESC_L2PT_BASE_ADDR_MASK)))

#define pgd_addr_end(addr, end)                                         \
 ({      unsigned long __boundary = ((addr) + L1_MAP_SIZE) & L1_MAP_MASK;  \
         (__boundary - 1 < (end) - 1) ? __boundary: (end);                \
 })

#define TTB_S		(1 << 1)
#define TTB_RGN_NC	(0 << 3)
#define TTB_RGN_OC_WBWA	(1 << 3)
#define TTB_RGN_OC_WT	(2 << 3)
#define TTB_RGN_OC_WB	(3 << 3)
#define TTB_NOS		(1 << 5)
#define TTB_IRGN_NC	((0 << 0) | (0 << 6))
#define TTB_IRGN_WBWA	((0 << 0) | (1 << 6))
#define TTB_IRGN_WT	((1 << 0) | (0 << 6))
#define TTB_IRGN_WB	((1 << 0) | (1 << 6))

/* PTWs cacheable, inner WBWA shareable, outer WBWA not shareable */
#define TTB_FLAGS_SMP	TTB_IRGN_WBWA | TTB_S | TTB_NOS | TTB_RGN_OC_WBWA

#ifndef __ASSEMBLY__

#ifdef CONFIG_MMU
#include <process.h>

extern void __mmu_switch(uint32_t l1pgtable_phys);

void pgtable_copy_kernel_area(uint32_t *l1pgtable);
void create_mapping(uint32_t *l1pgtable, uint32_t virt_base, uint32_t phys_base, uint32_t size);

uint32_t *new_l1pgtable(void);
void reset_l1pgtable(uint32_t *l1pgtable, bool remove);

void mmu_switch(uint32_t *l1pgtable);
void dump_pgtable(uint32_t *l1pgtable);

void duplicate_user_space(pcb_t *from, pcb_t *to);

void flush_tlb_all(void);
#endif /* CONFIG_MMU */

#endif


#endif /* MMU_H */

