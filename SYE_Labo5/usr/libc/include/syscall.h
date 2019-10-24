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

#ifndef SYSCALL_H
#define SYSCALL_H

/* System call codes, passed in r0 to tell the kernel which system call to do. */

#define syscallHalt			0
#define syscallExit			1
#define syscallExec			2
#define syscallWaitpid			3
#define syscallRead			4
#define syscallWrite			5
#define syscallFork			7
#define syscallReaddir			9
#define syscallChdir			10
#define syscallGetcwd			11
#define syscallCreate			12
#define syscallOpen			14
#define syscallClose			15
#define syscallThreadCreate		16
#define syscallThreadJoin		17
#define syscallThreadExit		18
#define syscallIoctl			20
#define syscallMkdir			21
#define syscallDup			22
#define syscallPipe			19
#define syscallDup2			23
#define syscallSchedSetParam 		25
#define syscallStat			34
#define syscallMmap			35
#define syscallEndProc			36
#define syscallSbrk			45
#define syscallExecve			50
#define syscallMutexInit		60
#define syscallMutexLock		61
#define syscallMutexUnlock		62


#ifndef __ASSEMBLY__

#include <bits/alltypes.h>

#include <pthread.h>
#include <types.h>

extern int errno;

/* The system call interface. These are the operations the Nachos kernel needs to
 * support, to be able to run user programs.
 *
 * Each of these is invoked by a user program by simply calling the
 * procedure; an assembly language stub stores the syscall code (see above) into $r0
 * and executes a syscall instruction. The kernel exception handler is then invoked.
 */

/* Halt the Nachos machine by calling Machine.halt(). Only the root process (the first
 * process, executed by UserKernel.run()) should be allowed to execute this syscall. Any
 * other process should ignore the syscall and return immediately and set errno to EPERM.
 */
void halt();

/* PROCESS MANAGEMENT SYSCALLS: exit(), exec(), fork(), waitpid() */

/**
 * Terminate the current process immediately. Any open file descriptors belonging to the
 * process are closed. Any children of the process no longer have a parent process.
 *
 * status is returned to the parent process as this process's exit status and can be
 * collected using the join syscall. A process exiting normally should set status to 0.
 *
 * exit() never returns.
 */
void sys_exit(int status) __attribute__((noreturn));

/**
 * Execute the program stored in the specified file, with the specified arguments.
 * The current process image is replaced by the program found in the file.
 *
 * file is a null-terminated string that specifies the name of the file containing the
 * executable. Note that this string must include the ".elf" extension.
 *
 * argc specifies the number of arguments to pass to the child process. This number must
 * be non-negative.
 *
 * argv is an array of pointers to null-terminated strings that represent the arguments
 * to pass to the child process. argv[0] points to the first argument, and argv[argc-1]
 * points to the last argument.
 *
 * exec() returns the child process's process ID, which can be passed to join(). On
 * error, returns -1.
 */
int exec(char *file, int argc, char *argv[]);
int execve(const char *pathname, int argc, char **argv, char **envp);

/**
 * This system call are used to wait for state changes in a child of the calling
 * process, and obtain information about the child whose state has changed.
 * A state change is considered to be: the child terminated; the child was stopped.
 *
 * By default, waitpid() waits only for terminated children, but this behavior
 * is modifiable via the options argument, as described above.
 *
 * If status is not NULL, waitpid() store status information in the int to which it
 * points. This integer can be inspected with the macros above (which take the
 * integer itself as an argument, not a pointer to it, as is done in waitpid()!)
 *
 * on success, returns the process ID of the child whose state has changed;
 * if WNOHANG was specified and one or more child(ren) specified by pid exist,
 * but have not yet changed state, then 0 is returned. On error, -1 is returned.
 */
pid_t waitpid(pid_t pid, int *status, int options);

/**
 * Fork a new process according to the standard UNIX fork system call.
 */
int fork(void);

/**
 * open - possible flags for open syscall
 */
#define O_RDONLY        00000001	/* open in read only mode */
#define O_WRONLY        00000002	/* open in write only mode */
#define O_RDWR          00000003	/* open in read+write mode */
#define O_CREAT         00000100        /* if the file does not exist it will be created */
#define O_EXCL		00000200	/* used with O_CREAT, ensure that this call creates the file */
#define O_TRUNC         00001000        /* if the file already exists and is a regular file and the open mode allows writing (i.e., is O_RDWR or O_WRONLY) it will be truncated to length 0. */
#define O_NONBLOCK      00004000	/* when possible, the file is opened in nonblocking mode.  */
#define O_DIRECTORY     00200000        /* if pathname is not a directory, cause the open to fail. */
#define O_CLOEXEC      	00400000	/* Enable the close-on-exec flag for the new file descriptor. */

/**
 * open - open and possibly create a file or device
 *
 * Given a pathname for a file, open() returns a file descriptor, a small, nonnegative
 * integer for use in subsequent system calls (read(2), write(2), seek(2), etc.).
 * The file descriptor returned by a successful call will be the lowest-numbered file
 * descriptor not currently open for the process.
 *
 * open() return the new file descriptor, or -1 if an error occurred
 * (in which case, errno is set appropriately).
 */
int open(const char *pathname, int flags);

int sys_write(int fd, const void *buf, size_t count);
int sys_read(int fd, void *buf, size_t count);

/**
 * Close a file descriptor, so that it no longer refers to any file or stream and may be
 * reused.
 *
 * If the file descriptor refers to a file, all data written to it by write() will be
 * flushed to disk before close() returns.
 * If the file descriptor refers to a stream, all data written to it by write() will
 * eventually be flushed (unless the stream is terminated remotely), but not
 * necessarily before close() returns.
 *
 * The resources associated with the file descriptor are released. If the descriptor is
 * the last reference to a disk file which has been removed using unlink, the file is
 * deleted (this detail is handled by the file system implementation).
 *
 * Returns 0 on success, or -1 if an error occurred.
 */
int close(int fd);

/**
 * The ioctl() function manipulates the underlying device parameters of
 * special files. In particular, many operating characteristics of character
 * special files (e.g., terminals) may be controlled with ioctl()
 * requests. The argument fd must be an open file descriptor.
 *
 * The second argument is a device-dependent request code. The third
 * argument is an untyped pointer to memory.
 *
 * Returns 0 on success or -1 if an error occurred, and errno is set.
 */
int ioctl(int fd, int cmd, void *val);

/**
 * This IOCTL command returns the number of column and lines of the given
 * fd. the result is returned in the following form:
 * int val[0] = #lines
 * int val[1] = #columns
 */
#define IOR_CONSOLE_SIZE 1

/**
 * Clone a thread.
 *
 * Returns the thread ID on success to the parent and 0 to the child, or
 * -1 on error and set errno.

 * entryState=true: first invocation by the parent (routine and args has to be passed)
 * entryState=false: second invocation by the child (which retrieved routine and args from the kernel)
 */
int thread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);

/**
 * The thread_join() function waits for the thread specified by thread to
 * terminate. If that thread has already terminated, then thread_join()
 * returns immediately. The thread specified by thread must be joinable.
 *
 * If retval is not NULL, then thread_join() copies the exit status of
 * the target thread (i.e., the value that the target thread supplied to
 * thread_join(3)) into the location pointed to by *retval.
 *
 * On success, thread_join() returns 0; on error, it returns an error
 * number.
 */
int thread_join(pthread_t thread, void **value_ptr);

/**
 * The calling thread is terminated. This function does not return.
 */
void thread_exit(int *exit_status);

/**
 * Duplicate an open file descriptor.
 *
 * Example: 
 * 	dup2(1, 2); // Redirects messages from stderr to stdout
 *
 * Returns -1 on error, or fildes2 on success.
 */
int dup(int oldfd);

/**
 *
 */
int dup2(int orig, int copy);

/**
 *
 */
int pipe(int pipe_fd[2]);

/**
 * Change priority of given thread
 *
 * Returns 0 on success, or -1 on error and set errno.
 */
int sched_setparam(int threadId, int priority);

/**
 * The ioctl() function manipulates the underlying device parameters of
 * special files. In particular, many operating characteristics of character
 * special files (e.g., terminals) may be controlled with ioctl()
 * requests. The argument fd must be an open file descriptor.
 *
 * The second argument is a device-dependent request code. The third
 * argument is an untyped pointer to memory.
 *
 * Returns 0 on success or -1 if an error occurred, and errno is set.
 */
int ioctl(int fd, int cmd, void *val);

/**
 * getPID syscall
 */
int getpid();

/*
 * sbrk syscall
 *
 * Grows heap
 *
 * increment: number of bytes to add to heap. If increment is not a multiple of PAGE_SIZE,
 * 	it is internally incremented to the next whole page size. (1025 -> 2048 for example)
 * return: Base address of newly allocated space. If there is not enough space left in
 * 	the heap, return -1 and sets ERRNO to ENOMEM. If increment equals 0, return current heap top.
 */

void *sbrk(int increment);


/*
 * First attempt of mutex implementation in the user space. Mainly used, at the moment,
 * for debugging kernel mutexes.
 */
void mutex_init(void);
void mutex_lock(void);
void mutex_unlock(void);


#endif /* __ASSEMBLY__ */

#endif /* SYSCALL_H */
