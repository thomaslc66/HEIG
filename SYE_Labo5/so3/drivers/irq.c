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
 * - 2016: Alexandre Malki
 *
 * Generic IRQs and IRQ controller handling API
 *
 */

/* irq.c
 *
 * Generic IRQs and IRQ controller handling API
 *
 */


#include <common.h>
#include <fdt.h>
#include <tinyprintf.h>
#include <softirq.h>
#include <stddef.h>

#include <asm/hardware/irq.h>
#include <asm/processor.h>
#include <asm/hardware/irq.h>
#include <mach/intc.h>

struct intc_ops *ops_irq;

static irqdesc_t irqdesc[NR_IRQS];

irqdesc_t *get_irqdesc(int irq) {
	return &irqdesc[irq];
}

int irq_process(int irq) {
	int ret;

	if (irqdesc[irq].action != NULL)
		ret = irqdesc[irq].action(irq);

	return ret;
}

int irq_handle(void) {

	if (!ops_irq)
		return -1;

	ops_irq->intc_handle();

	return 0;
}

int irq_bind(int irq, irq_handler_t handler, int flags) {
	if (!ops_irq)
		return -1;

	DBG("Binding irq %d with action at %x\n", irq, handler);
	irqdesc[irq].action = handler;
	irqdesc[irq].irqflags = flags;

	return 0;

}

int irq_mask(int irq) {
	if (!ops_irq)
		return -1;

	return ops_irq->intc_mask(irq);
}

int irq_unmask(int irq) {
	if (!ops_irq)
		return -1;

	return ops_irq->intc_unmask(irq);
}

int irq_enable(int irq) {
	if (!ops_irq)
		return -1;

	ops_irq->intc_enable(irq);
	ops_irq->intc_unmask(irq);

	return 0;
}

int irq_disable(int irq) {
	if (!ops_irq)
		return -1;

	ops_irq->intc_mask(irq);
	ops_irq->intc_disable(irq);

	return 0;
}

void irq_init(void) {
	int i;

	for (i = 0; i < NR_IRQS; i++) {
		irqdesc[i].action = NULL;

		irqdesc[i].irqflags = 0;
	}

	/* Initialize the softirq subsystem */
	softirq_init();
}
