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
 */

#ifndef IRQ_H
#define IRQ_H

#include <common.h>
#include <fdt.h>

enum irqreturn {
	IRQ_NONE		= (0 << 0),
	IRQ_HANDLED		= (1 << 0),
	IRQ_WAKE_THREAD		= (1 << 1),
};

typedef enum irqreturn irqreturn_t;
typedef irqreturn_t (*irq_handler_t)(int);

typedef enum  { IRQF_NO_REENABLE } irqflags_t;

typedef struct irqdesc {
	irq_handler_t action;
	irqflags_t irqflags;
} irqdesc_t;


extern int arch_irq_init(void);
extern void setup_arch(void);

/* IRQ controller */
struct intc_ops {
    int (*intc_enable)(unsigned int irq);
    int (*intc_disable)(unsigned int irq);
    int (*intc_mask)(unsigned int irq);
    int (*intc_unmask)(unsigned int irq);
    int (*intc_handle)(void);
};

extern struct intc_ops *ops_irq;

int irq_process(int irq);

void irq_init(void);

int irq_bind(int irq, irq_handler_t handler, int irqflags);

int irq_mask(int irq);
int irq_unmask(int irq);
int irq_enable(int irq);
int irq_disable(int irq);

struct irq_desc *irq_to_desc(unsigned int irq);

int request_irq(unsigned int irq, irq_handler_t handler, unsigned long flags, const char *name, void *dev);

void set_irq_flags(unsigned int irq, unsigned int iflags);

void free_irq(unsigned int irq, void *dev_id);

typedef	void (*irq_flow_handler_t)(unsigned int irq, struct irq_desc *desc);

void irq_set_handler(unsigned int irq, irq_flow_handler_t handle);

#endif /* IRQ_H */
