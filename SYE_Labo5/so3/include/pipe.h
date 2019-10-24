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

#ifndef PIPE_H
#define PIPE_H

#include <memory.h>
#include <mutex.h>
#include <sync.h>

#define PIPE_READER	0
#define PIPE_WRITER	0

#define PIPE_SIZE	PAGE_SIZE

struct pipe_desc {

	/* Mutex to access critical parts */
	struct mutex lock;

	/* Main buffer of this pipe */
	void *pipe_buf;

	/* The two global FD for each extremity */
	uint32_t gfd[2];

	/* Consumer */
	uint32_t pos_read;

	/* Producer */
	uint32_t pos_write;

	/* Waiting queue for managing empty pipe */
	completion_t wait_for_writer;

	/* Waiting queue for managing full pipe */
  	completion_t wait_for_reader;
};
typedef struct pipe_desc pipe_desc_t;

int do_pipe(int pipefd[2]);

#endif /* PIPE_H */
