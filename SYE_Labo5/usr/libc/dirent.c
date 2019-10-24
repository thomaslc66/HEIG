/*
 * dirent.c
 *
 *  Created on: Sep 10, 2013
 *      Author: romain
 */

#include <string.h>
#include <dirent.h>

DIR *opendir(const char *name) {
	int ret = open(name, O_DIRECTORY);
	return ret < 0 ? NULL : (DIR *)ret;
}

void closedir(DIR *dir) {
	close((int) dir);
}
