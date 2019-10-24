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
 * - September 2015: Raphaël Buache
 */

#include <asm/hardware/spi.h>
#include <tinyprintf.h>

struct spi_ops *ops_spi;

char spi_config(struct config_spi *config) {
	if (!ops_spi)
		return -1;
	return ops_spi->spi_config(config);
}

int spi_read(void) {
	if (!ops_spi)
		return -1;
	return ops_spi->spi_read();
}

int spi_write(int data) {
	if (!ops_spi)
		return -1;
	return ops_spi->spi_write(data);
}
int spi_write_fifo(int data) {
	if (!ops_spi)
		return -1;
	return ops_spi->spi_write_fifo(data);
}
int spi_enable_fifo(void (*callback)(void)) {
	if (!ops_spi)
		return -1;
	return ops_spi->spi_enable_fifo(callback);
}
