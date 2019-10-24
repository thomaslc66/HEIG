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
 * - August 2015: Raphaël Buache
 */

#include "so3_gpio.h"
#include "stddef.h"
#include "tinyprintf.h"

struct so3_gpio_ops *ops_gpio;

int gpio_config_dir(int num, int output) {
	if (!ops_gpio)
		return -1;
	return ops_gpio->gpio_config_dir(num, output);
}

int gpio_set(int num, int status) {
	if (!ops_gpio)
		return -1;
	return ops_gpio->gpio_set(num, status);
}

int gpio_get(int num) {
	if (!ops_gpio)
		return -1;
	return ops_gpio->gpio_get(num);
}

int gpio_interrupt(int num, void (*callback)(void)) {
	if (!ops_gpio)
		return -1;
	return ops_gpio->gpio_interrupt(num, callback);
}
