@ exceptions.S
@
@ entry points and handlers for exceptions and interrupts
@
@ based on explanations in "Building Bare Metal ARM Systems with GNU"
@ http://www.state-machine.com/arm/Building_bare-metal_ARM_with_GNU.pdf
@ and on U-Boot implementation

#include <asm/processor.h>

/* use the special section (.vectors.text), to enable fine-tuning
 * of the placement of this section inside the linker script
 */
.section ".vectors.text", "ax"

.globl _vectors
.globl ret_from_fork
.globl __get_syscall_args_ext

.extern _start

_vectors:   b   _start @ reset
            ldr pc, _undefined_instruction
            ldr pc, _syscall_interrupt
            ldr pc, _prefetch_abort
            ldr pc, _data_abort
            ldr pc, _not_used
            ldr pc, _irq
            ldr pc, _fiq

_undefined_instruction: .word undefined_instruction
_syscall_interrupt:     .word syscall_interrupt
_prefetch_abort:        .word prefetch_abort
_data_abort:            .word data_abort
_not_used:              .word not_used
_irq:                   .word irq
_fiq:                   .word fiq
_pad:                   .word 0x12345678 @ now 16*4=64

.extern irq_handle
.extern syscall_handle
.extern dumpstack
.extern __prefetch_abort
.extern __data_abort

.extern schedule_isr

@ exception handlers
.align  5
undefined_instruction:
    b  undefined_instruction

@ IRQs are off
@ ARM EABI: the syscall nr is stored in r7
.align  5
syscall_interrupt:
    stmfd sp!, {r1-r12, lr}  @ Store registers, r0 will be overwritten

    mrs r4, spsr             @ Get spsr
    stmfd sp!, {r4}          @ Store spsr onto stack

    sub	sp, sp, #8
    stmia sp, {sp, lr}^		 @ Store sp_usr and lr_usr

	cpsie   i 				 @ Re-enable interrupts

    bl syscall_handle

@ The stack pointer is at 14 * 4 bytes under its top.
__ret_from_fork:

	cpsid	i

	ldmia sp, {sp, lr}^
	add	sp, sp, #8

    ldmfd sp!, {r4}          @ Get spsr from stack
    msr spsr, r4             @ Restore spsr
    ldmfd sp!, {r1-r12, pc}^ @ Restore registers but keep r0 (return value)

@ Used at entry point of a fork'd process (setting the return value to 0)
ret_from_fork:
	mov		r0, #0
	b		__ret_from_fork

@ Get the additional arguments linked to the syscall.
@ The ABI convention is described in crt0.S of the libc.
@ r7 contains the syscall number
@ r10 contains the address of the errno variable
__get_syscall_args_ext:

	str		r7, [r0]
	str		r10, [r1]

	mov 	pc, lr

.align  5
prefetch_abort:

	mrc	p15, 0, r0, c6, c0, 2		@ get IFAR
	mrc	p15, 0, r1, c5, c0, 1		@ get IFSR

    b __prefetch_abort

.align  5
data_abort:

	mrc	p15, 0, r1, c5, c0, 0		@ get FSR
	mrc	p15, 0, r0, c6, c0, 0		@ get FAR

    b __data_abort

.align  5
not_used:
    b not_used

.align  5
irq:

    @ IRQ mode (lr_irq, sp_irq, cpsr_irq)

    @ Store original r0, and lr_irq in the IRQ stack sp = sp_irq
    @ sp_irq is a simple array declared in arch/arm/setup.c (so address can be ascending)

    str 	r0, [sp]		@ original r0
    str 	lr, [sp, #4]	@ lr_irq

    mrs 	r0, spsr 		@ to preserve irq bit
    str		r0, [sp, #8]	@ spsr_irq

    mov		r0, sp			@ to maintain a reference on sp_irq; r0 will not be affected after mode switch

    @ Now switch back to SVC. IRQs are disabled
    mrs		lr, cpsr

    bic		lr, lr, #MODE_MASK
    orr		lr, lr, #SVC_MODE

    @ switch to SVC
    msr		cpsr, lr

    @ --- SVC mode from now on ---

    @ On the stack, we preserve {spsr, sp, lr, pc} from the current sp location
    str		lr, [sp, #-8]   @ current lr

    @ preserve spsr for future IRQ enabling
    ldr		lr, [r0, #8]   @ retrieve spsr_irq
    str		lr, [sp, #-16] @ location of spsr_irq (hence cpsr right before the interrupt)

	@ Get original lr (as before irq)

	ldr 	lr, [r0, #4]	@ retrieve lr_irq
	sub 	lr, lr, #4		@ Adjust the lr since it is automatically set from pc (in advance of 2 instructions due to the pipeline)
	str 	lr, [sp, #-4]   @ future pc at exit

	str 	sp, [sp, #-12] @ preserve sp

	sub 	sp, sp, #16	   @ adjust for the call to IRQ handler, sp points to spsr_irq

	ldr 	r0, [r0] @ original r0

    stmfd 	sp!, {r0-r12}
	
	@ r4 will keep the *real* spsr
	ldr		r4, [sp, #13*4]  @ Keep a reference to the spsr

	@ Need to store sp_usr and lr_usr if we come from the user mode
	and		r4, r4, #MODE_MASK
	cmp		r4, #USR_MODE

	@ If yes...
	subeq	sp, sp, #8
	stmeqia	sp, {sp, lr}^

    bl 		irq_handle

	@ Give the opportunity to pending softirq to be executed (IRQs off, but can be (synchronously) preempted)
    bl 		do_softirq

	@ Check again
	cmp		r4, #USR_MODE

	@ If issued from the user mdode
	ldmeqia	sp, {sp, lr}^
	addeq	sp, sp, #8

    ldmfd 	sp!, {r0-r12}

    ldr 	lr, [sp], #4        @ get the saved spsr and adjust the stack pointer
    msr		spsr, lr

    @ Now, we retrieve the final registers, sp will be adjusted automatically
    ldmia 	sp, {sp, lr, pc}^

.align  5
fiq:
    b  fiq
