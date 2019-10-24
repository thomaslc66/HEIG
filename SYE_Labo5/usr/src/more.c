
#include <unistd.h>
#include <syscall.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <bits/ioctl.h>

#define BUFSIZE 1024

char buf[BUFSIZE];
struct winsize wsz;

int main(int argc, char **argv) {
	int quit = 0;
	int fd = STDIN_FILENO, nb_bytes, line_max, columns_max;
	int cpt_columns = -1, cpt_line = 0;
	int err;
	char key;

	if (argc > 2) {
		printf("Usage: more <file>\n");
		return 1;
	}

	if (argc == 2) {
		fd = open(argv[1], O_RDONLY);
		if (fd == -1) {
			printf("Error #%d:\n  Unable to open %s\n", errno, argv[1]);
			return 2;
		}
	}
	/* Get number of lines and columns */
	err = ioctl(STDOUT_FILENO, TIOCGWINSZ, &wsz);
	if (err != 0) {
		printf("Errno: %d\n  ioctl error %d\n", errno, err);
		return 3;
	}

	line_max = wsz.ws_row;
	columns_max = wsz.ws_col;

	nb_bytes = BUFSIZE;

	while ((nb_bytes = read(fd, buf, BUFSIZE)) > 0) {

		int i;

		for (i = 0; i < nb_bytes; i++) {
			cpt_columns++;

		  if ((int) buf[i] == 9) { /* Horizontal TAB */
			cpt_columns += 7 - (cpt_columns % 8);
			if (cpt_columns >= columns_max) {
				cpt_columns = 8;
				cpt_line++;
				putchar(13);
				putchar(10);
			  }
		  } else
			if (cpt_columns == columns_max) { /* End of line */
				cpt_columns = -1;
				cpt_line++;
				putchar(13);
				putchar(10);
			} else if ((int) buf[i] == 10) { /* Line feed in text */
				cpt_columns = -1;
				cpt_line++;

			}

			if (cpt_line == (line_max - 2)) {
				if ((int) buf[i] == 10)
					putchar(buf[i++]); /* print Line feed before ---MORE--- */
				cpt_line = 0;

				printf("\n--MORE--"); fflush(stdout);

				key = getc(stderr);
				if ((key == 'q') || (key == 'Q')) {
					quit = 1;
					break;
				}

				putchar('\n');
			}

			putchar(buf[i]);
		}
		if (quit)
			break;
	}
	putchar('\n');

	return 0;
}


