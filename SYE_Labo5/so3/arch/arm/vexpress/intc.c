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
 * - 2014: Romain Bornet,
 * - 2014-2017: Daniel Rossier
 * - 2016-2017: Alexandre Malki
 *
 */

#if 0
#define DEBUG
#endif

#include <common.h>
#include <device.h>
#include <driver.h>

#include <asm/hardware/irq.h>
#include <stddef.h>
#include <asm/io.h>
#include <mach/intc.h>
#include <tinyprintf.h>

static struct intc_regs *regs;

static dev_info_t irq_info;
struct intc_ops vexpress_intc_ops;

static int vexpress_intc_init(dev_info_t *info) {

	int i;

	/* init HAL */
	ops_irq = &vexpress_intc_ops;
	memcpy(&irq_info, info, sizeof(dev_info_t));

	DBG("%s\n", __FUNCTION__);

	regs = (struct intc_regs *) info->base;

	/* Initialize distributor and CPU interface of GIC.
	 * See Linux implementation as reference: http://lxr.free-electrons.com/source/arch/arm/common/gic.c?v=3.2
	 */

	/* Distributor interface initialization */

	/* Disable distributor */
	iowrite32(&regs->gicd_ctlr, 0);

	/* All interrupts level triggered, active low by default */
	for (i = 32; i < NR_IRQS; i += 16) {
		iowrite32(&regs->gicd_icfgr[i/16], 0);
	}

	/* Target CPU for all IRQs is CPU0 */
	for (i = 32; i < NR_IRQS; i += 4) {
		iowrite32(&regs->gicd_itargetsr[i/4], 0x01010101);
	}

	/* Priority for all interrupts is the highest (value 0) */
	for (i = 32; i < NR_IRQS; i += 4) {
		iowrite32(&regs->gicd_ipriorityr[i/4], 0);
	}

	/* Disable all interrupts  */
	for (i = 32; i < NR_IRQS; i += 32) {
		iowrite32(&regs->gicd_icenabler[i/32], 0xffffffff);
	}

	/* Enable distributor */
	iowrite32(&regs->gicd_ctlr, 1);

	/* CPU interface initialization */

	/* Handle SGI (0-15) and PPI interrupts (16-31) separately */
	/* Disable all PPI and SGI interrupts */
	iowrite32(&regs->gicd_icenabler[0], 0xffffffff);

	/* Priority for all SGI and PPI interrupts is the highest (value 0) */
	for (i = 0; i < 32; i+=4) {
		iowrite32(&regs->gicd_ipriorityr[i/4], 0);
	}

	/* Allow all priorities */
	iowrite32(&regs->gicc_pmr, 0xff);

	/* Enable CPU interface */
	iowrite32(&regs->gicc_ctlr, 1);

	DBG("%s 0x%08x bit %d\n", __func__, (unsigned int) &regs->gicd_spendsgirn[54/32], 54 % 32);
	return 0;
}

static int vexpress_intc_mask(unsigned int irq) {

	/* Disable/mask IRQ using the clear-enable register */
	iowrite32(&regs->gicd_icenabler[irq/32], 1 << (irq % 32));
	return 0;
}

static int vexpress_intc_unmask(unsigned int irq) {

	/* Enable/unmask IRQ using the set-enable register */
	iowrite32(&regs->gicd_isenabler[irq/32], 1 << (irq % 32));

	return 0;
}

static int vexpress_intc_enable(unsigned int irq) {

	vexpress_intc_unmask(irq);

	return 0;
}

static int vexpress_intc_disable(unsigned int irq) {
	vexpress_intc_mask(irq);
	return 0;
}

/* TODO : Complete this function */
static int vexpress_intc_handle(void) {
	int irq_nr;
	int irqstat;

	do {
		irqstat = ioread32(&regs->gicc_iar);
		irq_nr = irqstat & GICC_IAR_INT_ID_MASK;

		if ((irq_nr < 15) || (irq_nr > 1021))
			return 0;

		irq_process(irq_nr);

		iowrite32(&regs->gicc_eoir, irqstat);

	} while (true);

	return 0;
}

struct intc_ops vexpress_intc_ops = {
		.intc_enable = vexpress_intc_enable,
		.intc_disable = vexpress_intc_disable,
		.intc_mask = vexpress_intc_mask,
		.intc_unmask = vexpress_intc_unmask,
		.intc_handle = vexpress_intc_handle
};

REGISTER_DRIVER(vexpress_intc, "vexpress,vexpress-gic", vexpress_intc_init);

