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
 * - April 2017: Xavier Ruppen
 * - June 2017: Daniel Rossier
 */

#ifndef VFS_H
#define VFS_H

#include <types.h>
#include <stat.h>
#include <stddef.h>

/* File access mode flags */
#define O_RDONLY 00000001	/* open in read only mode */
#define O_WRONLY 00000002	/* open in write only mode */
#define O_RDWR 00000003		/* open in read+write mode */

/* Operating mode flags */
#define O_CLOEXEC 00400000	/* Enable the close-on-exec flag for the new file descriptor */
#define O_NONBLOCK 00004000	/* when possible, the file is opened in nonblocking mode.  */

/* Open-time flags */
#define O_CREAT 00000100	/* if the file does not exist it will be created */
#define O_TRUNC 00001000	/* if the file already exists and is a regular file and the open
				   mode allows writing (i.e., is O_RDWR or O_WRONLY) it will
				   be truncated to length 0. */
#define O_DIRECTORY 00200000	/* if pathname is not a directory, cause the open to fail. */
#define O_EXCL 00000200		/* used with O_CREAT, ensure that this call creates the file */
#define O_APPEND      02000    /* open a file and append data to the end of it*/


#define MAX_FS_REGISTERED 4
#define MAX_FDS 128

#define FILENAME_MAX 100

#define STDIN 0
#define STDOUT 1
#define STDERR 2

/* Types of entry */
#define VFS_TYPE_FILE		0
#define VFS_TYPE_DIR		1
#define VFS_TYPE_PIPE		2

/* Device type (borrowed from Linux) */
#define DT_UNKNOWN	0
#define DT_FIFO		1	/* Like pipe */
#define DT_CHR		2	/* Char device */
#define DT_DIR		4	/* DIR entry */
#define DT_BLK		6	/* Block device */
#define DT_REG		8	/* Regular file */
#define DT_LNK		10	/* Symbolic link */
#define DT_SOCK		12	/* Socket device */

struct file_operations {
	int (*open)(int fd, const char *path);
	int (*close)(int fd);
	int (*read)(int fd, void *buffer, int count);
	int (*write)(int fd, void *buffer, int count);
	int (*lseek)(size_t);
	int (*ioctl)(int fd, unsigned long cmd, unsigned long args);
	void *(*readdir)(int fd);
	int (*mkdir)(int fd, void *);
	int (*stat)(const char *path, struct stat *st);
	int (*unlink)(int fd, void *);
	int (*mount)(const char *);
	int (*unmount)(const char *);
	void (*clone)(int fd);
};

struct fd {
	/*  FD number */
	uint32_t val;
	uint32_t flags_operating_mode;
	uint32_t flags_access_mode;
	uint32_t flags_open;
	uint32_t type;
	 
	/* Reference counter to keep the object alive when greater than 0. */
	uint32_t ref_count;

	/* List of callbacks */
	struct file_operations *fops;
	/* Private data of fd */
	void *priv;
};

/* Syscall accessible from userspace */
int do_open(const char *filename, int flags);
int do_read(int fd, void *buffer, int count);
int do_write(int fd, void *buffer, int count);
void *do_readdir(int fd);
void do_close(int fd);
int do_dup(int oldfd);
int do_dup2(int oldfd, int newfd);
int do_stat(const char *path , struct stat *st);
int do_ioctl(int fd, unsigned long cmd, unsigned long args);

/* VFS common interface */
int vfs_get_gfd(int localfd);
struct file_operations *vfs_get_fops(uint32_t gfd);
int vfs_refcount(int gfd);
void vfs_init(void);
int vfs_open(struct file_operations *fops, uint32_t type);
int vfs_close(int gfd);
void vfs_set_privdata(int gfd, void *data);
void *vfs_get_privdata(int gfd);
int vfs_clone_fd(int *gfd_src, int *gfd_dst);

uint32_t vfs_get_access_mode(int fd);
uint32_t vfs_get_open_mode(int fd);
uint32_t vfs_get_operating_mode(int fd);

void vfs_set_access_mode(int gfd, uint32_t flags_access_mode);
int vfs_set_open_mode(int gfd, uint32_t flags_open_mode);
int vfs_set_operating_mode(int gfd, uint32_t flags_operating_mode);

#endif /* VFS_H */
