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
 * - 2015-2017: Daniel Rossier
 * - May-June 2017: Xavier Ruppen
 *
 */

#ifndef ELF_H
#define ELF_H

#include <elf-struct.h>

#define ELF_MAXSIZE (128 * SZ_1K)

/* ELF Binary image related information */
struct elf_img_info {
	Elf32_Ehdr *header;
	Elf32_Shdr *sections;
	Elf32_Phdr *segments; /* program header */
	char **section_names;
	void *file_buffer;
	uint32_t segment_page_count;
};
typedef struct elf_img_info elf_img_info_t;

uint8_t *elf_load_buffer(const char *filename);

void elf_load_sections(elf_img_info_t *elf_img_info);
void elf_load_segments(elf_img_info_t *elf_img_info);

void elf_clean_image(elf_img_info_t *elf_img_info);

#endif /* ELF_H */
