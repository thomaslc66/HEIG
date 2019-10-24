@ SO3 Kernel entry point

#include <linkage.h>

#include <generated/autoconf.h>

#include <asm/processor.h>
#include <asm/mmu.h>
#include <asm/memory.h>
#include <thread.h>

.global _start
.global _fdt_addr

.extern clear_bss

.extern configure_l1pgtable

.extern __stack_base

.extern __vectors_start


.section ".head.text","ax"

_start:

  @ r1 = machine id
  @ r2 = atags pointer or FDT address

  @ Make sure we start in SVC mode

  msr  	cpsr_c, #PSR_F_BIT | PSR_I_BIT | SVC_MODE @ ensure svc mode and irqs disabled

  @ Set vector table at address ___vectors_start
  ldr 	r1, .LCvectors
  mcr 	p15, 0, r1, c12, c0, 0

  @ Preserve the (physical address of) device tree base in r9
  mov 	r9, r2

  @ Initialize stack pointers for current mode (normal case if no MMU is used)
  ldr  	sp, .LCstack_base
  add	sp, sp, #THREAD_STACK_SIZE

  @ Up to here, a stack should be initialized

#ifdef CONFIG_MMU
  @ Set up the MMU

  b		mmu_setup

#endif /* CONFIG_MMU */

__kernel_main:

  ldr	r0, =_fdt_addr
  str	r9, [r0]

  @ C main entry point
  b 	kernel_start

  @ never returns...



#ifdef CONFIG_MMU

  .align 2

mmu_setup:

  @ Use a temporary stack
  adrl	sp, temp_stack

  @ Store the virtual address which will be used to continue
  @ the execution after the MMU enabled.
  ldr	r8, .LCvirt_entry

  @ Refer to the 1st-level page table
  ldr	r6, =CONFIG_RAM_BASE + L1_SYS_PAGE_TABLE_OFFSET

  mov	r0, r6
  mov	r1, r9 @ fdt addr
  mov   r7, lr
  bl 	configure_l1pgtable
  mov 	lr, r7


	mov	r0, #0
	mcr	p15, 0, r0, c7, c10, 4	@ drain write buffer

	mcr	p15, 0, r0, c8, c7, 0	@ flush I,D TLBs

	mrc	p15, 0, r0, c1, c0, 0	@ read control reg
	bic	r0, r0, #1 << 28	@ clear SCTLR.TRE
	orr	r0, r0, #0x5000		@ I-cache enable, RR cache replacement
	orr	r0, r0, #0x003c		@ write buffer
	bic	r0, r0, #2		@ A (no unaligned access fault)
	orr	r0, r0, #1 << 22	@ U (v6 unaligned access model)
								@ (needed for ARM1176)
#ifdef CONFIG_MMU

	mrc   	p15, 0, r5, c2, c0, 2   @ read ttb control reg
	orr		r0, r0, #1				@ MMU enabled
	mov		r1, #0xffffffff			@ all domains are manager
	bic     r5, r5, #1 << 31        @ 32-bit translation system
	bic     r5, r5, #3 << 0         @ use only ttbr0
	mcr		p15, 0, r6, c2, c0, 0	@ load page table pointer
	mcr		p15, 0, r1, c3, c0, 0	@ load domain access control
	mcr   	p15, 0, r5, c2, c0, 2   @ load ttb control
#endif
	mcr	p15, 0, r0, c7, c5, 4	@ ISB
	mcr	p15, 0, r0, c1, c0, 0	@ load control register
	mrc	p15, 0, r0, c1, c0, 0	@ and read it back
	mov	r0, #0
	mcr	p15, 0, r0, c7, c5, 4	@ ISB



  @ Readjust the stack
  ldr	sp, .LCstack_base
  add	sp, sp, #THREAD_STACK_SIZE

  @ Keep executing in the kernel space
  mov	pc, r8

 #endif /* CONFIG_MMU */


.ltorg

_fdt_addr:
  .word 	0

	.align	2
__v7_setup_stack:
	.space	4 * 11				@ 11 registers

.align 8

@ Before MMU is enabled, we cannot refer to the normal stack as declared in the linker script
temp_stack_bottom:
	.space 1024
temp_stack:

.LCvirt_entry:
  .word __kernel_main

.LCstack_base:
  .word __stack_base

.LCvectors:
  .word __vectors_start
