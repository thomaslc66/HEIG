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
 */

#include <common.h>   /* struct uart_ops */

#include <device.h>
#include <driver.h>
#include <heap.h>

#include <asm/io.h>             /* ioread/iowrite macros */
#include <types.h>

#include <asm/hardware/serial.h>    /* bits and regs definitions */

#include <mach/uart.h>

static dev_info_t uart_info =
{
  .base = UART_BASE,
};

static int vexpress_uart_put_byte(char c) {

	while ((ioread16(uart_info.base + UART01x_FR) & UART01x_FR_TXFF)) ;

	iowrite16(uart_info.base + UART01x_DR, c);

	return 1;
}


static char vexpress_uart_get_byte(void) {
	/* Block while nothing available */
	if (ioread8(uart_info.base + UART01x_FR) & UART01x_FR_RXFE)
		return -1;

	return ioread16(uart_info.base + UART01x_DR);
}

static int vexpress_uart_init(dev_info_t *dev) {

	/* Init UART */
	ops_uart = (struct uart_ops *) malloc(sizeof(struct uart_ops));
	if (ops_uart == NULL) {
		printk("%s: failed during malloc().\n", __func__);
		return -1;
	}

	ops_uart->put_byte = vexpress_uart_put_byte;
	ops_uart->get_byte = vexpress_uart_get_byte;

	memcpy(&uart_info, dev, sizeof(dev_info_t));

	return 0;
}

void __ll_put_byte(char c) {

	vexpress_uart_put_byte(c);

}

REGISTER_DRIVER(vexpress_uart, "vexpress,vexpress-uart", vexpress_uart_init);
