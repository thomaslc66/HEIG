/*
 * ls.c
 *
 *  Created on: 20 août 2008
 *      Author: drossier
 */
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


/*
 * Forking process for each dir...
 */
int main(int argc, char **argv) {
	DIR *stream;
	struct dirent  *p_entry;
	char *dir;

	if (argc == 1) {
		dir = ".";
	} else if (argc == 2) {
		dir = argv[1];
	} else {
		printf("Usage: ls [DIR]\n");
		exit(1);
	}

	stream = opendir(dir);
	if (stream == NULL)
		exit(1);

	while ((p_entry = readdir(stream)) != NULL) {

		if ((argc > 1) && !strcmp(argv[1], "-l")) {
			if (p_entry->d_type)
				printf("d ");
			else
				printf("r ");
			printf("%dB\t", p_entry->d_size);
		}
		printf("%s\n", p_entry->d_name);

	}


  exit(0);
}

