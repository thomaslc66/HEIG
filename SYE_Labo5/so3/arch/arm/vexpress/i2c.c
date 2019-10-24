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


#include <common.h>
#include <fdt.h>      /* struct dev_infos */

#include <stddef.h>
#include <tinyprintf.h>

#include <asm/hardware/i2c.h>

struct i2c_ops vexpress_i2c_ops;

/********* led rgb **********/
static int led_reg_r = 0x00;
static int led_reg_g = 0x00;
static int led_reg_b = 0x00;
static int led_reg_pwm = 0x00;
static int led_reg_mode = 0x00;

static int speed;
static int slave_addr;


static int vexpress_i2c_arch_init(struct dev_infos *infos) {
	return 0;
}

static int vexp_i2c_init(int requested_speed, int slaveadd)
{
	led_reg_r = 0x00;
	led_reg_g = 0x00;
	led_reg_b = 0x00;
	led_reg_pwm = 0x00;
	led_reg_mode = 0x00;

	speed = requested_speed;
	slave_addr = slaveadd;

	ops_i2c = &vexpress_i2c_ops;

	return 0;
}

static int i2c_begin(int expected_start_status, char addr)
{
	int status = 0;
	return status;
}

static int vexp_i2c_read(unsigned char dev, unsigned int addr, int alen, unsigned char *data, int length)
{
	int status = 0;

	/* begin i2c write to send the address bytes */
	status = i2c_begin(0, 0);

	/* begin i2c read to receive eeprom data bytes */
	if (status == 0)
		status = i2c_begin(0, 0);

	/* Emule the RGB led */
	if(dev == 0x040 && addr == 0x82 && alen == 1) {
		*data = led_reg_r;
	}
	else if (dev == 0x040 && addr == 0x84 && alen == 1) {
		*data = led_reg_g;
	}
	else if (dev == 0x040 && addr == 0x83 && alen == 1) {
		*data = led_reg_b;
	}
	else if (dev == 0x040 && addr == 0x0c && alen == 1) {
		*data = led_reg_pwm;
	}
	else if (dev == 0x040 && addr == 0x00 && alen == 1) {
		*data = led_reg_mode;
	}
	else {
		*data = 0x00;
	}

	/* return 0 or status of first failure */
	return status;
}

static int vexp_i2c_write(unsigned  char dev, unsigned int addr, int alen, unsigned char *data, int length)
{
	int status = 0;

	/* begin i2c write to send the eeprom adress bytes then data bytes */
	status = i2c_begin(0, 0);

	/* Emule the RGB led */
	if (dev == 0x40 && addr == 0x82 && alen == 1 && length == 1) {
		led_reg_r = *data;
	}
	else if (dev == 0x40 && addr == 0x84 && alen == 1 && length == 1) {
		led_reg_g = *data;
	}
	else if (dev == 0x40 && addr == 0x83 && alen == 1 && length == 1) {
		led_reg_b = *data;
	}
	else if (dev == 0x40 && addr == 0x0c && alen == 1 && length == 1) {
		led_reg_pwm = *data;
	}
	else if (dev == 0x40 && addr == 0x00 && alen == 1 && length == 1) {
		led_reg_mode = *data;
	}

	if (led_reg_mode == 0x80 && led_reg_pwm == 0x2a) {
		printk("\nLED RGB %d %d %d\n",led_reg_r, led_reg_g, led_reg_b);
	}

	/* return 0 or status of first failure */
	return status;

}

struct i2c_ops vexpress_i2c_ops = {
		.i2c_init = vexp_i2c_init,
		.i2c_write = vexp_i2c_write,
		.i2c_read = vexp_i2c_read
};

REGISTER_DRIVER(vexpress_i2c, "vexpress,i2c-bus", vexpress_i2c_arch_init);
