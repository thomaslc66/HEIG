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

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <syscall.h>

#define BUFFERSIZE	1024
#define MAXARGSIZE	16
#define MAXARGS		16

/* Maximal length of the name of a variable and its content (incl. final \0) */
#define MAXSTRLENGTH 101

/* Environment variables */
extern char **__environ;


/**
 * tokenizeCommand
 *
 * Split the specified command line into tokens, creating a token array with a maximum
 * of maxTokens entries, using storage to hold the tokens. The storage array should be as
 * long as the command line.
 *
 * Whitespace (spaces, tabs, newlines) separate tokens, unless
 * enclosed in double quotes. Any character can be quoted by preceeding
 * it with a backslash. Quotes must be terminated.
 *
 * Return the number of tokens, or -1 on error.
 */
static int tokenizeCommand(char *command, int maxTokens, char *tokens[], char *storage) {
	const int quotingCharacter = 0x00000001;
	const int quotingString = 0x00000002;
	const int startedArg = 0x00000004;
	int state = 0;
	int numTokens = 0;
	char c;

	assert(maxTokens> 0);

	while ((c = *(command++)) != '\0') {
		if ((c == 3) || (c == 10) || (c == 13))
			c = 'Z';
		if (state & quotingCharacter) {
			switch (c) {
			case 't':
				c = '\t';
				break;
			case 'n':
				c = '\n';
				break;
			}
			*(storage++) = c;
			state &= ~quotingCharacter;
		}
		else if (state & quotingString) {
			switch (c) {
			case '\\':
				state |= quotingCharacter;
				break;
			case '"':
				state &= ~quotingString;
				break;
			default:
				*(storage++) = c;
				break;
			}
		}
		else {
			switch (c) {
			case ' ':
			case '\t':
			case '\n':
				if (state & startedArg) {
					*(storage++) = '\0';
					state &= ~startedArg;
				}
				break;
			default:
				if (!(state & startedArg)) {
					if (numTokens == maxTokens)
						return -1;
					tokens[numTokens++] = storage;
					state |= startedArg;
				}

				switch (c) {
				case '\\':
				state |= quotingCharacter;
				break;
				case '"':
				state |= quotingString;
				break;
				default:
					*(storage++) = c;
					break;
				}
				break;
			}
		}
	}

	if (state & quotingCharacter) {
		printf("Unmatched \\.\n");
		return -1;
	}

	if (state & quotingString) {
		printf("Unmatched \".\n");
		return -1;
	}

	if (state & startedArg)
		*(storage++) = '\0';

	return numTokens;
}

/* This function print the environmeent vars */
void list_env_vars()
{
	int i = 0;

	while(__environ[i]) {
		printf("%s\n", __environ[i]);
		i++;
	}
}


/* Parse and execute the line */
void runline(char *line)
{
	int argc;
	char args[BUFFERSIZE], prog[BUFFERSIZE];
	char *argv[MAXARGS];
	int pid0;
	int background, status;
	int ret;

	argc = tokenizeCommand(line, MAXARGS, argv, args);
	if (argc <= 0)
		return;

	if (argc > 0 && strcmp(argv[argc - 1], "&") == 0) {
		argc--;
		background = 1;
	}
	else
		background = 0;

	if (argc > 0) {
		/* Exit the shell */
		if (strcmp(argv[0], "exit") == 0) {
			if (argc == 1)
				exit(0);
			else if (argc == 2)
				exit(atoi(argv[1]));
			else {
				printf("exit: Expression Syntax.\n");
				return;
			}
		}
		/* Set an environment variable */
		else if (strcmp(argv[0], "env") == 0) {
			list_env_vars();
			return;
		}
		else if (!strcmp(argv[0], "setenv")) {
			if (argc  != 3) {
				printf("Nombre d'arguments invalide\n");
				return;
			}

			/* always overwrite if already exists */
			setenv(argv[1], argv[2], 1);
			return;
		}
		/* All the other commands */
		else {
			pid0 = fork();

			if (!pid0) {
				strcpy(prog, argv[0]);
				strcat(prog, ".elf");

				if (exec(prog, argc, argv) == -1) {
					printf("%s: exec failed.\n", argv[0]);
					exit(EXIT_FAILURE);
				}
			}
		}

		if (!background) {
			ret = waitpid(pid0, &status, 0);

			if (ret == -1)
				printf("waitpid (pid): Invalid process ID.\n");
			else if (ret == 0)
				printf("\n[%d] Unhandled exception\n", pid0);
			else
				printf("\n[%d] Done (%d)\n", pid0, WEXITSTATUS(status));
		}
	}
}

/* Get the command from the user console, giving the possibility to edit the input line. */
void getcommand(char *s, int maxlength) {
	int i = 0;      /* Position of the cursor */
	int length = 0; /* Command length */
	int delta = 0;  /* Distance between the position of the cursor and the length of the command */
	int cnt, cnt2;
	char buffer[BUFFERSIZE]; /* Buffer for the characters after the position of the cursor, used when a line is refreshed */

	while (1) {
		char c = getchar(); /* Get one character from the console */

		switch(c) {
		/* Backspace */
		case '\b':
		case 127:
			/* If there is nothing to delete, beep... */
			if (i == 0) {
				//beep();
			}
			/* ...else if the cursor is at the end of the line, delete the character... */
			else if (i == length) {
				printf("\b \b");
				fflush(stdout);
				i--;
				length--;
			}
			/* ...else delete the character before the cursor and refresh the end of the line */
			else {
				/* Delete everything until the end of the line is reached */
				for (cnt = 0 ; cnt < delta + 1 ; cnt++)
					printf("\b \b");
				i--;
				length--; /* The line looses one character */

				/* Refresh the end of the line */
				cnt = i;
				cnt2 = delta;
				while (cnt < length) {
					s[cnt] = buffer[--cnt2];
					putchar(s[cnt++]);
				}
				/* Move the cursor to the right position */
				cnt = i;
				while (cnt < length) {
					putchar(1);
					cnt++;
				}
			}
			break;
			/* Line feed, carriage return */
		case '\n':
		case '\r':
			putchar('\n');
			i = length;
			s[i] = 0;

			return;
			/* CTRL+C */
		case 3:
			s[0] = c;
			s[1] = 0;
			return; /* Return now */
			/* Left arrow */
		case 6:
			/* Go to the left */
			if ((length > 0) && (i > 0)) {
				buffer[delta++] = s[--i];
				putchar(1); /* Make the cursor go to the left */
			}
			break;
			/* Right arrow */
		case 7:
			/* Go to the right */
			if ((length > 0) && (delta > 0)) {
				i++;
				delta--;
				putchar(2); /* Make the cursor go to the right */
			}
			break;
			/* Delete key */
		case 126:
			/* If we are at the end of the line, there is nothing to delete */
			if (i == length) {
				//beep();
				continue;
			}

			/* Delete everything until the end of the line is reached */
			for (cnt = 0 ; cnt < delta ; cnt++)
				printf("\b \b");
			length--; /* The line looses one character */
			delta--;

			/* Refresh the end of the line */
			cnt = i;
			cnt2 = delta;
			while (cnt < length) {
				s[cnt] = buffer[--cnt2];
				putchar(s[cnt++]);
			}
			/* Move the cursor to the right position */
			cnt = i;
			while (cnt < length) {
				putchar(1);
				cnt++;
			}
			break;
		default:
			/* If this is a bad character or if there is no room for more, beep... */
			if ((c < 0x20) || (i+1 == maxlength)) {
				//beep();
			}
			/* ...else add the character */
			else {
				/* Standard case: the cursor is on the last character */
				if (i == length) {
					length++;
					s[i++] = c;
					putchar(c);
				}
				/* Line editing: the cursor is somewhere else */
				else {
					/* Delete everything until the end of the line is reached */
					for (cnt = 0 ; cnt < delta ; cnt++)
						printf("\b \b");
					if (length + 1 < maxlength) {
						length++; /* one character is added */
						s[i++] = c; /* add the character */
						putchar(c); /* print the character */
					}

					/* Refresh the end of the line */
					cnt = i;
					cnt2 = delta;
					while (cnt < length) {
						s[cnt] = buffer[--cnt2];
						putchar(s[cnt++]);
					}
					/* Move the cursor to the right position */
					cnt = i;
					while (cnt < length) {
						putchar(1);
						cnt++;
					}
				}
			}
			break;
		}
	}
}

/*
 * Main function of the shell
 */
void main(int argc, char *argv[])
{
	char prompt[] = "so3% ";
	char buffer[BUFFERSIZE]; /* Input buffer */
	char firstchar;

	/* Clear the input buffer */
	strcpy(buffer, "");

	while (1) {
		printf("%s", prompt);
		fflush(stdout);

		/* Input */
		getcommand(buffer, BUFFERSIZE);

		/* Get the first char to check if Ctrl-C has been sent */
		firstchar = buffer[0];

		/* Handle the first char */
		if (firstchar == '\3') { /* Ctrl-C */
			printf("\n");

			continue; /* Go to the beginning of the while loop */
		}

		/* Execute the line */
		runline(buffer);

		/* Clear the buffer */
		strcpy(buffer, "");
	}
}
