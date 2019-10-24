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


#ifndef VEXPRESS_TIMER_H
#define VEXPRESS_TIMER_H

#include <types.h>

#define V2M_PA_CS7		0x1c000000

#define V2M_PERIPH_OFFSET(x)	(x << 16)

#define V2M_TIMER01		(V2M_PA_CS7 + V2M_PERIPH_OFFSET(17))
#define V2M_TIMER23		(V2M_PA_CS7 + V2M_PERIPH_OFFSET(18))

#define TIMER_RATE			1000000   /* 0xf4240 */

#define TIMER_LOAD      0x00
#define TIMER_VALUE     0x04
#define TIMER_CTRL      0x08
#define TIMER_CTRL_ONESHOT      (1 << 0)
#define TIMER_CTRL_32BIT        (1 << 1)
#define TIMER_CTRL_DIV1         (0 << 2)
#define TIMER_CTRL_DIV16        (1 << 2)
#define TIMER_CTRL_DIV256       (2 << 2)
#define TIMER_CTRL_IE           (1 << 5)        /* Interrupt Enable (versatile only) */
#define TIMER_CTRL_PERIODIC     (1 << 6)
#define TIMER_CTRL_ENABLE       (1 << 7)

#define TIMER_INTCLR    				0x0c

/* Bits and regs definitions */
/* System controller (SP810) register definitions */
#define SP810_TIMER0_ENSEL	(1 << 15)
#define SP810_TIMER1_ENSEL	(1 << 17)
#define SP810_TIMER2_ENSEL	(1 << 19)
#define SP810_TIMER3_ENSEL	(1 << 21)

struct systimer {
	u32 timer0load;		/* 0x00 */
	u32 timer0value;
	u32 timer0control;
	u32 timer0intclr;
	u32 timer0ris;
	u32 timer0mis;
	u32 timer0bgload;
	u32 timer1load;		/* 0x20 */
	u32 timer1value;
	u32 timer1control;
	u32 timer1intclr;
	u32 timer1ris;
	u32 timer1mis;
	u32 timer1bgload;
};

struct sysctrl {
	u32 scctrl;		/* 0x000 */
	u32 scsysstat;
	u32 scimctrl;
	u32 scimstat;
	u32 scxtalctrl;
	u32 scpllctrl;
	u32 scpllfctrl;
	u32 scperctrl0;
	u32 scperctrl1;
	u32 scperen;
	u32 scperdis;
	u32 scperclken;
	u32 scperstat;
	u32 res1[0x006];
	u32 scflashctrl;	/* 0x04c */
	u32 res2[0x3a4];
	u32 scsysid0;		/* 0xee0 */
	u32 scsysid1;
	u32 scsysid2;
	u32 scsysid3;
	u32 scitcr;
	u32 scitir0;
	u32 scitir1;
	u32 scitor;
	u32 sccntctrl;
	u32 sccntdata;
	u32 sccntstep;
	u32 res3[0x32];
	u32 scperiphid0;	/* 0xfe0 */
	u32 scperiphid1;
	u32 scperiphid2;
	u32 scperiphid3;
	u32 scpcellid0;
	u32 scpcellid1;
	u32 scpcellid2;
	u32 scpcellid3;
};


#endif /* VEXPRESS_TIMER_H */
