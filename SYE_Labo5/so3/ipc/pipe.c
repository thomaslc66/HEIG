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
 * - June 2017: Alexandre Malki, Daniel Rossier
 *
 */


#include <errno.h>
#include <heap.h>
#include <limits.h>
#include <list.h>
#include <pipe.h>
#include <vfs.h>
#include <schedule.h>


/*
 * Get the other end (extremity) based on a gfd.
 */
static int otherend(uint32_t gfd) {
	struct pipe_desc *pd = (struct pipe_desc *) vfs_get_privdata(gfd);

	if (!pd)
		return -EINVAL;

	return ((pd->gfd[0] == gfd) ? pd->gfd[1] : pd->gfd[0]);
}

/*
 * Check if the pipe is full
 */
bool pipe_full(pipe_desc_t *pd) {
	return (((pd->pos_write + 1) % PIPE_SIZE) == pd->pos_read);
}

/*
 * Check if the pipe is empty
 */
bool pipe_empty(pipe_desc_t *pd) {
	return (pd->pos_write == pd->pos_read);
}

/*
 * Read some bytes from the pipe associated to @gfd
 * @suspend tells if the thread must be suspended if there is no data (actually,
 * it may be the case that the thread has already consumed some bytes, in this case
 * it will proceed with the available bytes).
 */
static int pipe_read_byte(int gfd, char *value, bool suspend)
{
	pipe_desc_t *pd = (pipe_desc_t *) vfs_get_privdata(gfd);

	/* While no data to read, place thread in waiting state */
	while (suspend && pipe_empty(pd)) {

		/* FIXME : timeout  ?*/

		mutex_unlock(&pd->lock);

		wait_for_completion(&pd->wait_for_writer);

		if (pipe_empty(pd) && (vfs_refcount(otherend(gfd)) == 0))
			return -1;

		mutex_lock(&pd->lock);


	}
	if (pipe_empty(pd))
		return 0;

	value[0] = ((char *) pd->pipe_buf)[pd->pos_read]; /* Read value from buffer */

	/* Update circular read index */
	pd->pos_read = (pd->pos_read + 1) % PIPE_SIZE;

	return 1; /* One byte read successfully */
}

static int pipe_read(int gfd, void *buffer, int count)
{
	int pos, ret;
	bool first;
	pipe_desc_t *pd = (pipe_desc_t *) vfs_get_privdata(gfd);

	/* Sanity checks*/
	if (!buffer || (count <= 0)) {
		set_errno(EPIPE);
		return -1;
	}

 	mutex_lock(&pd->lock);

 	if ((vfs_refcount(otherend(gfd)) == 0) && pipe_empty(pd)) {
		/* no writers left, error */
 		set_errno(EPIPE);
 		mutex_unlock(&pd->lock);
		return -1;
 	}

	first = true;
	pos = 0;
	do {
		ret = pipe_read_byte(gfd, (char *) buffer + pos, first);
		if (ret < 0) {
			set_errno(EPIPE);
			mutex_unlock(&pd->lock);

			return -1;
		}

		first = false;

		if (ret)
			pos++;

	} while (ret && (pos < count));

	complete(&pd->wait_for_reader);

	mutex_unlock(&pd->lock);

	return pos; /* Effective number of read bytes */
}


/*
 * Write some bytes into the pipe associated to @gfd
 *
 * The pipe_desc lock is hold before at the entry of this function.
 */
static int pipe_write_byte(pipe_desc_t *pd, char value)
{
	/* While no empty locations, place thread in waiting state */
	while (pipe_full(pd)) {

		/* FIXME : timeout  ?*/
		mutex_unlock(&pd->lock);

		wait_for_completion(&pd->wait_for_reader);

		mutex_lock(&pd->lock);

		/* FIXME signal or timeout */
		if (pipe_full(pd))
			/* No readers left, error */
			return -1;

	}  

	((char *) pd->pipe_buf)[pd->pos_write] = value; /* Set new buffer value */

	/* Update circular write index */
	pd->pos_write = (pd->pos_write + 1) % PIPE_SIZE;

	return 1; /* 1 bytes successfully written */
}

static int pipe_write(int gfd, void *buffer, int count)
{
	int pos, ret;
	pipe_desc_t *pd = (pipe_desc_t *) vfs_get_privdata(gfd);

	/* Do Sanity checks */
	if (!buffer || (count <= 0)) {
		set_errno(EPIPE);
		return -1;
	}

	mutex_lock(&pd->lock);

	if ((vfs_refcount(otherend(gfd)) == 0) && pipe_full(pd)) {
		/* No readers left, error no space left */
		set_errno(EPIPE);
		mutex_unlock(&pd->lock);

		return -1;
	}

	for (pos = 0; pos < count; pos++) {

		ret = pipe_write_byte(pd, *((char *) buffer + pos));
		if (ret < 0) {
			set_errno(EPIPE);
			mutex_unlock(&pd->lock);

			return -1;
		}
	}

	/* Waking up sleeping threads */
	complete(&pd->wait_for_writer);

	mutex_unlock(&pd->lock);

	return pos; /* Effective number of written bytes */
}

/* 
 * Close the reader or writer when the refcount is equal to 0.
 */
static int pipe_close(int gfd)
{
	struct pipe_desc *pd = vfs_get_privdata(gfd);
	uint32_t opflags = vfs_get_access_mode(gfd);
	void *privdata;

	privdata = vfs_get_privdata(gfd);
	ASSERT(privdata != NULL);

	/* Check if some threads are waiting on it, and if yes and the pipe has nobody
	 * connected on one extremity, it wakes up the waiting threads.
	 */
	if (opflags == O_RDONLY)
		complete(&pd->wait_for_reader);


	if (opflags == O_WRONLY)
		complete(&pd->wait_for_writer);


	/* If there is no reader/writer anymore (i.e. gfd->refcount = 0), we can
	 * destroy the pipe.
	 */

	if (vfs_refcount(otherend(gfd)) == 0) {
		free(pd->pipe_buf);
		free(pd);  /* Finally, free the main pipe descriptor */
	}

	return 0;
}

/*
 * Pipe file operations
 */
struct file_operations pipe_fops = {
		.read = pipe_read,
		.write = pipe_write,
		.close = pipe_close
};

/*
 * @brief This is the syscall interface
 *
 * @return an array of two file descriptors (in/out) to access the pipe.
 */

int do_pipe(int pipefd[2]) {

	/* Allocated two file descriptor */
	pipe_desc_t *pd = (struct pipe_desc *) malloc(sizeof(pipe_desc_t));
	if (!pd) {
		printk("%s: heap overflow...\n", __func__);
		kernel_panic();
	}

	memset(pd, 0, sizeof(pipe_desc_t));

	pd->pipe_buf = malloc(PIPE_SIZE);
	if (pd->pipe_buf == NULL) {
		set_errno(ENOMEM);
		return -1;
	}

	/* Init internal structure members */

	mutex_init(&pd->lock);

	init_completion(&pd->wait_for_reader);
	init_completion(&pd->wait_for_writer);

	/* For next part use functions available in
	 * the vfs file.
	 * */

	/* Register ops in the gfd table
	 * open file descriptor for both side of
	 * the pipe 
	 * */

	 int fd_read  = vfs_open(&pipe_fops, VFS_TYPE_PIPE);
	 int fd_write = vfs_open(&pipe_fops, VFS_TYPE_PIPE);

	/* Keep a reference to the two gfd of this pipe:
	 * set the global fd inside the pipe descriptor
	 * for both side of the pipe
	 * */

	 int gfd_read  = vfs_get_gfd(fd_read);
	 int gfd_write = vfs_get_gfd(fd_write);

	 if(gfd_read == -1){
	 	printk("erreur de gfd_read");
	 	set_errno(ENOMEM);
	 	return -1;
	 }else{
		printk("fd globaux read \n");
		pd->gfd[0] = gfd_read;
	 }

 	 if(gfd_write == -1){
	 	printk("erreur de gfd_write");
	 	set_errno(ENOMEM);
	 	return -1;
	 }else{
		printk("fd globaux write\n");
		pd->gfd[1] = gfd_write;
	 }


	/* Set direction of the pipes
	 * Set access mode to both side:
	 * One side is read only, the other write only
	 * */
	 vfs_set_access_mode(gfd_read,O_RDONLY);
	 vfs_set_access_mode(gfd_write,O_WRONLY);

	/* Set private data of both global fds to
	 * pd to not loose track of the structure
	 */
	 vfs_set_privdata(gfd_read,(void *) pd);
	 vfs_set_privdata(gfd_write,(void *) pd);


	return 0;
}
