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
 * Contributors:
 *
 * - September 2015: Raphaël Buache
 *
 */

#ifndef INCLUDE_SO3_SPI_H_
#define INCLUDE_SO3_SPI_H_

#include <common.h>   /* struct so3_timer_ops */
#include <fdt.h>

#define SPI1_BASE_ADDRESS 0x48098000
#define SPI2_BASE_ADDRESS 0x4809A000
#define SPI3_BASE_ADDRESS 0x480B8000
#define SPI4_BASE_ADDRESS 0x480BA000

#define BIT0 (0x1)
#define BIT1 (0x1 << 1)
#define BIT2 (0x1 << 2)
#define BIT3 (0x1 << 3)
#define BIT4 (0x1 << 4)
#define BIT5 (0x1 << 5)
#define BIT6 (0x1 << 6)
#define BIT7 (0x1 << 7)
#define BIT8 (0x1 << 8)
#define BIT9 (0x1 << 9)
#define BIT10 (0x1 << 10)
#define BIT11 (0x1 << 11)
#define BIT12 (0x1 << 12)
#define BIT13 (0x1 << 13)
#define BIT14 (0x1 << 14)
#define BIT15 (0x1 << 15)
#define BIT16 (0x1 << 16)
#define BIT17 (0x1 << 17)
#define BIT18 (0x1 << 18)
#define BIT19 (0x1 << 19)
#define BIT20 (0x1 << 20)
#define BIT21 (0x1 << 21)
#define BIT22 (0x1 << 22)
#define BIT23 (0x1 << 23)
#define BIT24 (0x1 << 24)
#define BIT25 (0x1 << 25)
#define BIT26 (0x1 << 26)
#define BIT27 (0x1 << 27)
#define BIT28 (0x1 << 28)
#define BIT29 (0x1 << 29)
#define BIT30 (0x1 << 30)
#define BIT31 (0x1 << 31)

#define SPI1 ((SPI *)SPI1_BASE_ADDRESS)
#define SPI2 ((SPI *)SPI2_BASE_ADDRESS)
#define SPI3 ((SPI *)SPI3_BASE_ADDRESS)
#define SPI4 ((SPI *)SPI4_BASE_ADDRESS)

#define CHANNEL0 0
typedef volatile unsigned int vuint;

#define MCSPI_BASE			0x48098000
#define MCSPI4_OFFSET		0x00022000

#define MCSPI_SYSCONFIG_OFFSET		0x10
#define MCSPI_SYSSTATUS_OFFSET		0x14
#define MCSPI_IRQSTATUS_OFFSET		0x18
#define MCSPI_MODULCTRL_OFFSET		0x28
#define MCSPI_IRQENABLE_OFFSET		0x1C

/* SPI 4: only 1 channel */
#define MCSPI_CH1CONF_OFFSET		(0x2C+0x14*0)
#define MCSPI_CH1STAT_OFFSET		(0x30+0x14*0)
#define MCSPI_CH1CTRL_OFFSET		(0x34+0x14*0)
#define MCSPI_CH1TX_OFFSET			(0x38+0x14*0)

#define MCSPI4_SYSCONFIG		((vuint *)(MCSPI_BASE+MCSPI4_OFFSET+MCSPI_SYSCONFIG_OFFSET))
#define MCSPI4_SYSSTATUS		((vuint *)(MCSPI_BASE+MCSPI4_OFFSET+MCSPI_SYSSTATUS_OFFSET))
#define MCSPI4_IRQSTATUS		((vuint *)(MCSPI_BASE+MCSPI4_OFFSET+MCSPI_IRQSTATUS_OFFSET))
#define MCSPI4_MODULCTRL		((vuint *)(MCSPI_BASE+MCSPI4_OFFSET+MCSPI_MODULCTRL_OFFSET))
#define MCSPI4_IRQENABLE		((vuint *)(MCSPI_BASE+MCSPI4_OFFSET+MCSPI_IRQENABLE_OFFSET))
#define MCSPI4_CH1CONF			((vuint *)(MCSPI_BASE+MCSPI4_OFFSET+MCSPI_CH1CONF_OFFSET))
#define MCSPI4_CH1STAT			((vuint *)(MCSPI_BASE+MCSPI4_OFFSET+MCSPI_CH1STAT_OFFSET))
#define MCSPI4_CH1CTRL			((vuint *)(MCSPI_BASE+MCSPI4_OFFSET+MCSPI_CH1CTRL_OFFSET))
#define MCSPI_TX1			((vuint *)(MCSPI_BASE+MCSPI4_OFFSET+MCSPI_CH1TX_OFFSET))

#define MCSPI_SYSCONFIG_SRESET_BIT	(0x1 << 1)
#define MCSPI_SYSSTATUS_RESETDONE_BIT	(0x1 << 0)

#define MCSPI_MODULCTRL_MS_BIT		(0x1 << 2)
#define MCSPI_MODULCTRL_SINGLE_BIT	(0x1 << 0)

#define MCSPI_CHXCONF_ENFIFO_BITS	(0x3 << 27)

#define MCSPI_CHXCONF_TRM_BITS		(0x3 << 12)
#define MCSPI_CHXCONF_TRM_TX_BIT	(0x1 << 13)

#define MCSPI_CHXCONF_WL_BITS		(0x1F << 7)
#define MCSPI_CHXCONF_WL_32_BITS	(0x1F << 7)
#define MCSPI_CHXCONF_WL_8_BITS		(0x7 << 7)
#define MCSPI_CHXCONF_WL_16_BITS		(0xF << 7)

#define MCSPI_CHXCONF_FORCE		(0x1 << 20)

#define MCSPI_CHXCONF_IS_BIT		(0x1 << 18)
#define MCSPI_CHXCONF_DPE1_BIT		(0x1 << 17)
#define MCSPI_CHXCONF_DPE0_BIT		(0x1 << 16)

#define MCSPI_CHXCONF_EPOL_BIT		(0x1 << 6)

#define MCSPI_CHXCONF_CLKD_BITS		(0xF << 2)
#define MCSPI_CHXCONF_CLKD_128_BITS	(0xF << 2)

#define MCSPI_CHXCTRL_ENABLE_BIT	(0x1 << 0)

#define MCSPI_CHXSTAT_TXSTAT_BIT	(0x1 << 1)
#define MCSPI_CHXSTAT_EOT_BIT		(0x1 << 2)

struct SPI_Channel {
	volatile uint32_t     CHxCONF;
	volatile uint32_t     CHxSTAT;
	volatile uint32_t     CHxCTRL;
	volatile uint32_t     TXx;
	volatile uint32_t     RXx;
};

typedef struct {
	volatile uint32_t     REVISION;
	volatile uint32_t     RESERVED[3];
	volatile uint32_t     SYSCONFIG;
	volatile uint32_t     SYSSTATUS;
	volatile uint32_t     IRQSTATUS;
	volatile uint32_t     IRQENABLE;
	volatile uint32_t     WAKEUPENABLE;
	volatile uint32_t     SYST;
	volatile uint32_t     MODULCTRL;
	struct SPI_Channel	  CHANNEL[4];
	volatile uint32_t     XFERLEVEL;

} SPI;

struct config_spi {

	/*
	 * Nothing at the moment
	 */
};

struct spi_ops {

	char (*spi_config)(struct config_spi *config);
	int (*spi_read)(void);
	int (*spi_write)(int data);
	int (*spi_write_fifo)(int data);
	int (*spi_enable_fifo)(void (*callback)(void));

};

extern struct spi_ops *ops_spi;

char spi_config(struct config_spi *config);

int spi_read(void);

int spi_write(int data);

int spi_write_fifo(int data);

int spi_enable_fifo(void (*callback)(void));

#endif /* INCLUDE_SO3_SPI_H_ */
