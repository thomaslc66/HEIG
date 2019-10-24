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

#ifndef GPIO_H
#define GPIO_H

#include <asm/hardware/gpio.h>

/*
 * Generic GPIO API
 */

/* GPIO */
struct gpio_ops {
	int (*gpio_init)(struct dev_infos *infos);
	int (*gpio_config_dir)(int num, int dir);
	int (*gpio_set)(int num, int statut);
	int (*gpio_get)(int num);
	int (*gpio_interrupt)(int num, void (*callback)(void));
};

int gpio_request(int gp, const char *label);
void gpio_free(int gp);
void gpio_toggle_value(int gp);
int gpio_direction_input(int gp);
int gpio_direction_output(int gp, int value);
int gpio_get_value(int gp);
void gpio_set_value(int gp, int value);

#endif	/* GPIO_H */
