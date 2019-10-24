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
 * - August 2008, 2017: Daniel Rossier
 */

#include <syscall.h>

.extern __entryC

.data
.align 	4
.globl	errno

errno: .word	0x0

.text
.align  4

/* -------------------------------------------------------------
 * __start
 *	Initialize running a C program, by calling "main".
 * -------------------------------------------------------------
 */

	.globl	__start
__start:

	@ r0 points to the argument page

	bl		__entryC

	b		exit	 /* if we return from main, exit(return value) */

	nop

/* -------------------------------------------------------------
 * System call stubs:
 * - r0-r3 are used to store arguments
 * - r7 is used to store the syscall number
 * -------------------------------------------------------------
 */

.macro SYSCALLSTUB name, number
	.globl	\name		
\name:			

  stmfd sp!, {r7, r10, r11}

  mov	r7, #\number
  ldr	r10, =errno
  mov	r11, #0
  str	r11, [r10]

  swi	0

  ldmfd sp!, {r7, r10, r11}

  mov pc, lr

.endm

/* Syscalls stubs */
SYSCALLSTUB halt, 			syscallHalt
SYSCALLSTUB sys_write,		syscallWrite
SYSCALLSTUB sys_read, 		syscallRead
SYSCALLSTUB sys_exit, 		syscallExit
SYSCALLSTUB exec, 			syscallExec
SYSCALLSTUB execve,			syscallExecve
SYSCALLSTUB waitpid,		syscallWaitpid
SYSCALLSTUB fork, 			syscallFork
SYSCALLSTUB readdir, 		syscallReaddir
SYSCALLSTUB chdir, 			syscallChdir
SYSCALLSTUB getcwd, 		syscallGetcwd
SYSCALLSTUB creat, 			syscallCreate
SYSCALLSTUB open, 			syscallOpen
SYSCALLSTUB close, 			syscallClose
SYSCALLSTUB thread_create, 	syscallThreadCreate
SYSCALLSTUB thread_join, 	syscallThreadJoin
SYSCALLSTUB thread_exit, 	syscallThreadExit
SYSCALLSTUB ioctl,			syscallIoctl
SYSCALLSTUB mkdir,			syscallMkdir
SYSCALLSTUB stat,	 		syscallStat
SYSCALLSTUB dup,	 		syscallDup
SYSCALLSTUB pipe,     syscallPipe
SYSCALLSTUB dup2,     syscallDup2
SYSCALLSTUB end_process,    syscallEndProc
SYSCALLSTUB sbrk,			syscallSbrk
SYSCALLSTUB sched_setparam, syscallSchedSetParam

SYSCALLSTUB mutex_init,	    syscallMutexInit
SYSCALLSTUB mutex_lock,	    syscallMutexLock
SYSCALLSTUB mutex_unlock,   syscallMutexUnlock

