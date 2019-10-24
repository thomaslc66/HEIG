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
 * - 2014-2017: Daniel Rossier
 * - June 2017: Alexandre Malki
 */


#include <common.h>
#include <asm/hardware/serial.h>
#include <asm/processor.h>
#include <mutex.h>
#include <string.h>

#include <mach/uart.h>

struct uart_ops *ops_uart;
struct mutex serial_rlock;
struct mutex serial_wlock;

/* Outputs an ASCII string to console */
int serial_putc(char c) {
	if (ops_uart == NULL) {
		__ll_put_byte(c);
		return 1;
	} else
		return ops_uart->put_byte(c);
}

/* This function is in charge of accessing the lower layer of the uart driver */
static char serial_getc_internal(void) {
	return ops_uart->get_byte();
}

/* Get a byte from the UART. */
char serial_getc(void) {
	char ret = (char) -1;

	/* This function will get a byte but first take try to
	 * take the lock to access the uart */
	while (ret == (char) -1) {
		mutex_lock(&serial_rlock);
		ret = serial_getc_internal();
		mutex_unlock(&serial_rlock);

		if (ret == (char) -1) {
			/* This is a way to save some cpu time
			 * avoiding the host to suffer for nothing
			 */
			__asm("dsb");
			__asm("wfi");
		}
	}

	return ret;
}

/* Sends some bytes to the UART */
int serial_write(char *str, int len) {
	int i;
	uint32_t flags;

	mutex_lock(&serial_wlock);
	flags = local_irq_save();

	for (i = 0; i < len; i++)
		if (str[i] != 0)
			serial_putc(str[i]);

	local_irq_restore(flags);

	mutex_unlock(&serial_wlock);

	return len;
}

/* Gets at most len bytes into buf.
 * Puts a '\0' either replacing '\n' or at the end of buf.
 * Returns the number of characters written (excluding '\0'). */
static int serial_read_internal(char *buf, int len)
{
	int i = 0;
	while (1) {
		buf[i] = serial_getc_internal();

		if (buf[i] == -1) {
			continue;
		}

		if (buf[i] == '\r' || buf[i] == '\n') {
			/* replace '\r' or '\n' with '\0' */
			buf[i] = '\0';
			break;
		}

		if (i == len-2) {
			/* add '\0' in the last empty space */
			i++;
			buf[i] = '\0';
			break;
		}

		i++;
	}

	return i;
}

/* This is a wrapper of the internal function. You might want to 
 * user some mutex for the future*/
int serial_read(char *buf, int len) {
	return serial_read_internal(buf, len);
}


int serial_init(void)
{
	mutex_init(&serial_rlock);
	mutex_init(&serial_wlock);

	return 0;
}

/* This function will query the size of the serial terminal*/
int serial_gwinsize(struct winsize *wsz)
{

	/*
	 * The following code strongly depends on a patched version of Qemu which reacts
	 * to the '\254' ASCII code. When the emulated UART interface get this code, qemu
	 * queries the host via ioctl(stdout, TIOCGWINSZ) to retrieve the window size.
	 */

	/* We want to reserve the access to the uart read. */
	mutex_lock(&serial_rlock);
	if (serial_write(SERIAL_GWINSZ, 1) == 0) {
		mutex_unlock(&serial_rlock);
		return -1;
	}

	wsz->ws_row = serial_getc();
	wsz->ws_col = serial_getc();

	mutex_unlock(&serial_rlock);

	return 0;
}

#ifdef CONFIG_VEXPRESS
/*
 * Send a specific char code to Qemu to ask it to exit immediately.
 */
void send_qemu_halt(void) {

	serial_write(SERIAL_SO3_HALT, 1);

}

#endif
