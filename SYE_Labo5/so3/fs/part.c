
/*
 * (C) Copyright 2001
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#if 0
#define DEBUG
#endif

#include <common.h>
#include <heap.h>
#include <part.h>


struct block_drvr {
	char *name;
	block_dev_desc_t* (*get_dev)(int dev);
};

static const struct block_drvr block_drvr[] = {
	{ .name = "mmc", .get_dev = mmc_get_dev, },
	{ },
};

block_dev_desc_t *get_dev(const char *ifname, int dev)
{
	const struct block_drvr *drvr = block_drvr;
	block_dev_desc_t* (*reloc_get_dev)(int dev);
	char *name;

	if (!ifname)
		return NULL;

	name = drvr->name;

	while (drvr->name) {
		name = drvr->name;
		reloc_get_dev = drvr->get_dev;

		if (strncmp(ifname, name, strlen(name)) == 0)
			return reloc_get_dev(dev);
		drvr++;
	}
	return NULL;
}



/* ------------------------------------------------------------------------- */
/*
 * reports device info to the user
 */

#ifdef CONFIG_LBA48
typedef uint64_t lba512_t;
#else
typedef lbaint_t lba512_t;
#endif

/*
 * Overflowless variant of (block_count * mul_by / div_by)
 * when div_by > mul_by
 */
static lba512_t lba512_muldiv(lba512_t block_count, lba512_t mul_by, lba512_t div_by)
{
	lba512_t bc_quot, bc_rem;

	/* x * m / d == x / d * m + (x % d) * m / d */
	bc_quot = block_count / div_by;
	bc_rem  = block_count - div_by * bc_quot;
	return bc_quot * mul_by + (bc_rem * mul_by) / div_by;
}

void dev_print(block_dev_desc_t *dev_desc)
{
	lba512_t lba512; /* number of blocks if 512bytes block size */

	if (dev_desc->type == DEV_TYPE_UNKNOWN) {
		printk("not available\n");
		return;
	}

	switch (dev_desc->if_type) {
	case IF_TYPE_SCSI:
		printk("(%d:%d) Vendor: %s Prod.: %s Rev: %s\n",
			dev_desc->target,dev_desc->lun,
			dev_desc->vendor,
			dev_desc->product,
			dev_desc->revision);
		break;
	case IF_TYPE_ATAPI:
	case IF_TYPE_IDE:
	case IF_TYPE_SATA:
		printk("Model: %s Firm: %s Ser#: %s\n",
			dev_desc->vendor,
			dev_desc->revision,
			dev_desc->product);
		break;
	case IF_TYPE_SD:
	case IF_TYPE_MMC:
	case IF_TYPE_USB:
		printk("Vendor: %s Rev: %s Prod: %s\n",
			dev_desc->vendor,
			dev_desc->revision,
			dev_desc->product);
		break;
	case IF_TYPE_DOC:
		printk("device type DOC\n");
		return;
	case IF_TYPE_UNKNOWN:
		printk("device type unknown\n");
		return;
	default:
		printk("Unhandled device type: %i\n", dev_desc->if_type);
		return;
	}
	printk ("            Type: ");
	if (dev_desc->removable)
		printk ("Removable ");
	switch (dev_desc->type & 0x1F) {
	case DEV_TYPE_HARDDISK:
		printk ("Hard Disk");
		break;
	case DEV_TYPE_CDROM:
		printk ("CD ROM");
		break;
	case DEV_TYPE_OPDISK:
		printk ("Optical Device");
		break;
	case DEV_TYPE_TAPE:
		printk ("Tape");
		break;
	default:
		printk ("# %02X #", dev_desc->type & 0x1F);
		break;
	}
	printk ("\n");
	if (dev_desc->lba > 0L && dev_desc->blksz > 0L) {
		ulong mb, mb_quot, mb_rem, gb, gb_quot, gb_rem;
		lbaint_t lba;

		lba = dev_desc->lba;

		lba512 = (lba * (dev_desc->blksz/512));
		/* round to 1 digit */
		mb = lba512_muldiv(lba512, 10, 2048);	/* 2048 = (1024 * 1024) / 512 MB */

		mb_quot	= mb / 10;
		mb_rem	= mb - (10 * mb_quot);

		gb = mb / 1024;
		gb_quot	= gb / 10;
		gb_rem	= gb - (10 * gb_quot);
#ifdef CONFIG_LBA48
		if (dev_desc->lba48)
			printk ("            Supports 48-bit addressing\n");
#endif
#if defined(CONFIG_SYS_64BIT_LBA)
		printk("            Capacity: %ld.%ld MB = %ld.%ld GB (%Ld x %ld)\n",
			mb_quot, mb_rem,
			gb_quot, gb_rem,
			lba,
			dev_desc->blksz);
#else
		printk("            Capacity: %ld.%ld MB = %ld.%ld GB (%ld x %ld)\n",
			mb_quot, mb_rem,
			gb_quot, gb_rem,
			(ulong)lba,
			dev_desc->blksz);
#endif
	} else {
		printk("            Capacity: not available\n");
	}
}

void init_part(block_dev_desc_t * dev_desc)
{

	if (test_part_dos(dev_desc) == 0) {
		dev_desc->part_type = PART_TYPE_DOS;
		return;
	}

	dev_desc->part_type = PART_TYPE_UNKNOWN;
}


static void print_part_header(const char *type, block_dev_desc_t * dev_desc)
{
	printk ("\nPartition Map for ");
	switch (dev_desc->if_type) {
	case IF_TYPE_IDE:
		printk ("IDE");
		break;
	case IF_TYPE_SATA:
		printk ("SATA");
		break;
	case IF_TYPE_SCSI:
		printk ("SCSI");
		break;
	case IF_TYPE_ATAPI:
		printk ("ATAPI");
		break;
	case IF_TYPE_USB:
		printk ("USB");
		break;
	case IF_TYPE_DOC:
		printk ("DOC");
		break;
	case IF_TYPE_MMC:
		printk ("MMC");
		break;
	case IF_TYPE_HOST:
		printk("HOST");
		break;
	default:
		printk ("UNKNOWN");
		break;
	}
	printk (" device %d  --   Partition Type: %s\n\n",
			dev_desc->dev, type);
}

void print_part (block_dev_desc_t * dev_desc)
{

	switch (dev_desc->part_type) {
	return;
	case PART_TYPE_DOS:
		printk ("## Testing for valid DOS partition ##\n");
		print_part_header ("DOS", dev_desc);
		print_part_dos (dev_desc);
		return;
	}
	printk ("## Unknown partition table\n");
}


int get_partition_info(block_dev_desc_t *dev_desc, int part, disk_partition_t *info)
{
	switch (dev_desc->part_type) {

	case PART_TYPE_DOS:
		if (get_partition_info_dos(dev_desc, part, info) == 0) {
			DBG("## Valid DOS partition found ##\n");
			return 0;
		}
		break;

	default:
		break;
	}


	return -1;
}

int get_device(const char *ifname, const char *dev_str,
	       block_dev_desc_t **dev_desc)
{
	char *ep;
	int dev;

	dev = simple_strtoul(dev_str, &ep, 16);
	if (*ep) {
		printk("** Bad device specification %s %s **\n",
		       ifname, dev_str);
		return -1;
	}

	*dev_desc = get_dev(ifname, dev);
	if (!(*dev_desc) || ((*dev_desc)->type == DEV_TYPE_UNKNOWN)) {
		printk("** Bad device %s %s **\n", ifname, dev_str);
		return -1;
	}

	return dev;
}

#define PART_UNSPECIFIED -2
#define PART_AUTO -1
#define MAX_SEARCH_PARTITIONS 16
int get_device_and_partition(const char *ifname, const char *dev_part_str, block_dev_desc_t **dev_desc, disk_partition_t *info, int allow_whole_dev)
{
	int ret = -1;
	const char *part_str;
	char *dup_str = NULL;
	const char *dev_str;
	int dev;
	char *ep;
	int p;
	int part;
	disk_partition_t tmpinfo;

	/* If still no dev_part_str, it's an error */
	if (!dev_part_str) {
		printk("** No device specified **\n");
		goto cleanup;
	}

	/* Separate device and partition ID specification */
	part_str = strchr(dev_part_str, ':');
	if (part_str) {
		dup_str = strdup(dev_part_str);
		dup_str[part_str - dev_part_str] = 0;
		dev_str = dup_str;
		part_str++;
	} else {
		dev_str = dev_part_str;
	}

	/* Look up the device */
	dev = get_device(ifname, dev_str, dev_desc);
	if (dev < 0)
		goto cleanup;

	/* Convert partition ID string to number */
	if (!part_str || !*part_str) {
		part = PART_UNSPECIFIED;
	} else if (!strcmp(part_str, "auto")) {
		part = PART_AUTO;
	} else {
		/* Something specified -> use exactly that */
		part = (int)simple_strtoul(part_str, &ep, 16);
		/*
		 * Less than whole string converted,
		 * or request for whole device, but caller requires partition.
		 */
		if (*ep || (part == 0 && !allow_whole_dev)) {
			printk("** Bad partition specification %s %s **\n",
			    ifname, dev_part_str);
			goto cleanup;
		}
	}

	/*
	 * No partition table on device,
	 * or user requested partition 0 (entire device).
	 */
	if (((*dev_desc)->part_type == PART_TYPE_UNKNOWN) ||
	    (part == 0)) {
		if (!(*dev_desc)->lba) {
			printk("** Bad device size - %s %s **\n", ifname,
			       dev_str);
			goto cleanup;
		}

		/*
		 * If user specified a partition ID other than 0,
		 * or the calling command only accepts partitions,
		 * it's an error.
		 */
		if ((part > 0) || (!allow_whole_dev)) {
			printk("** No partition table - %s %s **\n", ifname,
			       dev_str);
			goto cleanup;
		}

		(*dev_desc)->log2blksz = LOG2((*dev_desc)->blksz);

		info->start = 0;
		info->size = (*dev_desc)->lba;
		info->blksz = (*dev_desc)->blksz;
		info->bootable = 0;
		strcpy((char *)info->type, BOOT_PART_TYPE);
		strcpy((char *)info->name, "Whole Disk");

		ret = 0;
		goto cleanup;
	}

	/*
	 * Now there's known to be a partition table,
	 * not specifying a partition means to pick partition 1.
	 */
	if (part == PART_UNSPECIFIED)
		part = 1;

	/*
	 * If user didn't specify a partition number, or did specify something
	 * other than "auto", use that partition number directly.
	 */
	if (part != PART_AUTO) {
		ret = get_partition_info(*dev_desc, part, info);
		if (ret) {
			printk("** Invalid partition %d **\n", part);
			goto cleanup;
		}

	} else {
		/*
		 * Find the first bootable partition.
		 * If none are bootable, fall back to the first valid partition.
		 */
		part = 0;
		for (p = 1; p <= MAX_SEARCH_PARTITIONS; p++) {
			ret = get_partition_info(*dev_desc, p, info);
			if (ret)
				continue;

			/*
			 * First valid partition, or new better partition?
			 * If so, save partition ID.
			 */
			if (!part || info->bootable)
				part = p;

			/* Best possible partition? Stop searching. */
			if (info->bootable)
				break;

			/*
			 * We now need to search further for best possible.
			 * If we what we just queried was the best so far,
			 * save the info since we over-write it next loop.
			 */
			if (part == p)
				tmpinfo = *info;
		}
		/* If we found any acceptable partition */
		if (part) {
			/*
			 * If we searched all possible partition IDs,
			 * return the first valid partition we found.
			 */
			if (p == MAX_SEARCH_PARTITIONS + 1)
				*info = tmpinfo;
		} else {
			printk("** No valid partitions found **\n");
			ret = -1;
			goto cleanup;
		}
	}
	if (strncmp((char *)info->type, BOOT_PART_TYPE, sizeof(info->type)) != 0) {
		printk("** Invalid partition type \"%.32s\""
			" (expect \"" BOOT_PART_TYPE "\")\n",
			info->type);
		ret  = -1;
		goto cleanup;
	}

	(*dev_desc)->log2blksz = LOG2((*dev_desc)->blksz);

	ret = part;
	goto cleanup;

cleanup:
	free(dup_str);
	return ret;
}
