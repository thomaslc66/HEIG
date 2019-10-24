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
 */



#include <stddef.h>
#include <tinyprintf.h>

#include <asm/hardware/timer.h>

struct timer_ops *ops_timer;

static timer_handler action;

int timer_start_oneshot(int delay_us) {
    if (!ops_timer)
    	return -1;

    return ops_timer->timer_start_oneshot(delay_us);
}

int timer_start_periodic(int period_us) {
	if (!ops_timer)
	    return -1;

    return ops_timer->timer_start_periodic(period_us);
}

int timer_stop(void) {
	if (!ops_timer)
	   	return -1;

    return ops_timer->timer_stop();
}

int timer_bind(timer_handler handler) {
	if (!ops_timer)
		return -1;
	action = handler;
	return 0;
}

int timer_handle_process(void) {
	if (!ops_timer)
		return -1;

	if (action != NULL)
		action();
	return 0;

}
