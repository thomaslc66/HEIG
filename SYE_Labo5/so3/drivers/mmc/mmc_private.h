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
 * - <month> 2017: <first_name> <last_name>
 */

/*
 * Copyright 2008,2010 Freescale Semiconductor, Inc
 * Andy Fleming
 *
 * Based (loosely) on the Linux code
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef _MMC_PRIVATE_H_
#define _MMC_PRIVATE_H_

#include <mmc.h>

extern int mmc_send_cmd(struct mmc *mmc, struct mmc_cmd *cmd,
			struct mmc_data *data);
extern int mmc_send_status(struct mmc *mmc, int timeout);
extern int mmc_set_blocklen(struct mmc *mmc, int len);

#ifndef CONFIG_SPL_BUILD

extern unsigned long mmc_berase(int dev_num, lbaint_t start, lbaint_t blkcnt);

extern ulong mmc_bwrite(int dev_num, lbaint_t start, lbaint_t blkcnt,
		const void *src);

#else /* CONFIG_SPL_BUILD */

/* SPL will never write or erase, declare dummies to reduce code size. */

static inline unsigned long mmc_berase(int dev_num, lbaint_t start,
		lbaint_t blkcnt)
{
	return 0;
}

static inline ulong mmc_bwrite(int dev_num, lbaint_t start, lbaint_t blkcnt,
		const void *src)
{
	return 0;
}

#endif /* CONFIG_SPL_BUILD */

#endif /* _MMC_PRIVATE_H_ */
