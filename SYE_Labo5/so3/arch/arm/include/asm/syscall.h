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
 * - April-June 2017: Xavier Ruppen
 * - June 2017: Alexandre Malki
 * - June 2017: Daniel Rossier
 *
 */

#ifndef ASM_ARM_SYSCALL_H
#define ASM_ARM_SYSCALL_H

#include <errno.h>
#include <types.h>


#define SYSINFO_DUMP_HEAP	0
#define SYSINFO_DUMP_SCHED	1
#define SYSINFO_TEST_MALLOC	2
#define SYSINFO_PRINTK		3

/*
 * Syscall number definition
 */

#define SYSCALL_EXIT			1
#define SYSCALL_EXEC 			2
#define SYSCALL_WAITPID			3
#define SYSCALL_READ 			4
#define SYSCALL_WRITE 			5
#define SYSCALL_FORK 			7
#define SYSCALL_READDIR			9
#define SYSCALL_OPEN 			14
#define SYSCALL_CLOSE			15
#define SYSCALL_THREAD_CREATE	16
#define SYSCALL_THREAD_JOIN		17
#define SYSCALL_THREAD_EXIT		18
#define SYSCALL_IOCTL			20
#define SYSCALL_DUP				22

#define SYSCALL_PIPE			19
#define SYSCALL_DUP2			23

#define SYSCALL_STAT			34
#define SYSCALL_SBRK			45

#define SYSCALL_EXECVE			50

#define SYSCALL_MUTEX_INIT		60
#define SYSCALL_MUTEX_LOCK		61
#define SYSCALL_MUTEX_UNLOCK	62

#define SYSCALL_SYSINFO			99
#define SYSCALL_THREAD_YIELD 	24

int syscall_handle(uint32_t, uint32_t, uint32_t, uint32_t);

void set_errno(uint32_t val);

#endif /* ASM_ARM_SYSCALL_H */
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
 * - April-June 2017: Xavier Ruppen
 * - June 2017: Alexandre Malki
 * - June 2017: Daniel Rossier
 *
 */

#ifndef ASM_ARM_SYSCALL_H
#define ASM_ARM_SYSCALL_H

#include <errno.h>
#include <types.h>


#define SYSINFO_DUMP_HEAP	0
#define SYSINFO_DUMP_SCHED	1
#define SYSINFO_TEST_MALLOC	2
#define SYSINFO_PRINTK		3

/*
 * Syscall number definition
 */

#define SYSCALL_EXIT			1
#define SYSCALL_EXEC 			2
#define SYSCALL_WAITPID			3
#define SYSCALL_READ 			4
#define SYSCALL_WRITE 			5
#define SYSCALL_FORK 			7
#define SYSCALL_READDIR			9
#define SYSCALL_OPEN 			14
#define SYSCALL_CLOSE			15
#define SYSCALL_THREAD_CREATE	16
#define SYSCALL_THREAD_JOIN		17
#define SYSCALL_THREAD_EXIT		18
#define SYSCALL_IOCTL			20
#define SYSCALL_DUP				22

#define SYSCALL_PIPE			19
#define SYSCALL_DUP2			23

#define SYSCALL_STAT			34
#define SYSCALL_SBRK			45

#define SYSCALL_EXECVE			50

#define SYSCALL_MUTEX_INIT		60
#define SYSCALL_MUTEX_LOCK		61
#define SYSCALL_MUTEX_UNLOCK	62

#define SYSCALL_SYSINFO			99
#define SYSCALL_THREAD_YIELD 	24

int syscall_handle(uint32_t, uint32_t, uint32_t, uint32_t);

void set_errno(uint32_t val);

#endif /* ASM_ARM_SYSCALL_H */
