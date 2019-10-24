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
 * - June 2016: Daniel Rossier
 */

#include <common.h>

#include <device.h>
#include <driver.h>
#include <softirq.h>
#include <schedule.h>
#include <time.h>

#include <asm/hardware/irq.h>      /* irq_xxx API */
#include <asm/io.h>   /* ioread/iowrite macros */

#include <mach/timer.h>    /* bits and regs definitions */
#include <mach/intc.h>

#include <asm/hardware/timer.h>
#include <stddef.h>
#include <tinyprintf.h>

static struct systimer *systimer_base;

static int timer_irq;

static dev_info_t timer_info;
struct timer_ops vexpress_timer_ops;

static irqreturn_t timer_isr(int irq) {

	/* clear the interrupt */
	iowrite32(&systimer_base->timer0intclr, 1);

	jiffies++;

	/* temporary here, but will registered as a timer later... */
	raise_softirq(SCHEDULE_SOFTIRQ);

	return IRQ_HANDLED;
}

unsigned long read_timer(void) {
	return ~ioread32(&systimer_base->timer0value);
}

static int vexpress_timer_init(dev_info_t *info) {

	/* init HAL */

	systimer_base =  (struct systimer *) info->base;

	ops_timer = &vexpress_timer_ops;
	memcpy(&timer_info, info, sizeof(dev_info_t));

	/* init speed -> read devicetree */ //TODO

	/* Pins multiplexing skipped here for simplicity (done by bootloader) */
	/* Clocks init skipped here for simplicity (done by bootloader) */

	/* Initialize Timer */

	iowrite32(&systimer_base->timer1control, 0);
	iowrite32(&systimer_base->timer1load, 0xffffffff);
	iowrite32(&systimer_base->timer1value, 0xffffffff);
	iowrite32(&systimer_base->timer1control, TIMER_CTRL_32BIT | TIMER_CTRL_ENABLE | TIMER_CTRL_PERIODIC);

	/* Bind ISR into interrupt controller */
	irq_bind(info->irq, timer_isr, 0);

	timer_irq = info->irq;

	return 0;
}

static int timer_start(int delay_ms, bool periodic) {

	unsigned long ctrl = TIMER_CTRL_32BIT | TIMER_CTRL_IE;
	unsigned long reload;

	/* Number of clock cycles to wait */

	reload = delay_ms * (TIMER_RATE / MSECS);

	iowrite32(&systimer_base->timer0control, ctrl);

	if (periodic) {

		printk("%s: setting up system timer periodic freq at %lx\n", __func__, reload);
		iowrite32(&systimer_base->timer0load, reload);
		ctrl |= TIMER_CTRL_PERIODIC | TIMER_CTRL_ENABLE;

	} else {

		/* period set, and timer enabled in 'next_event' hook */
		ctrl |= TIMER_CTRL_ONESHOT;

	}
	iowrite32(&systimer_base->timer0control, ctrl);

	/* Enable interrupt (IRQ controller) */
	irq_enable(timer_irq);

	return 0;
}

static int vexpress_timer_start_oneshot(int delay_us) {

	/* Start timer in oneshot mode */
	return timer_start(delay_us, false);
}

static int vexpress_timer_start_periodic(int period_us) {

	/* Start timer in periodic mode */
	return timer_start(period_us, true);
}

static int vexpress_timer_stop(void) {

	/* Disable IRQ in IRQ controller and in timer controller */
	irq_disable(timer_irq);

	return 0;
}

struct timer_ops vexpress_timer_ops = {
		.timer_start_oneshot = vexpress_timer_start_oneshot,
		.timer_start_periodic = vexpress_timer_start_periodic,
		.timer_stop = vexpress_timer_stop
};

REGISTER_DRIVER(vexpress_timer, "vexpress,timer-sp", vexpress_timer_init);
