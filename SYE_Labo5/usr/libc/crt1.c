extern char ** __environ;
/*
 * This entry code handles the initialization of the BSS section.
 *
 */
extern char __bss_start[], __bss_end[];
extern int main(int argc, char **argv);
extern void mutex_init(void);

int __entryC(void *args) {

	char *cp = __bss_start;
	int argc;
	char **argv;

	/* Zero out BSS */
	while (cp < __bss_end)
		*cp++ = 0;

	/*
	 * Prepare argc & argv
	 * The arguments are placed in a argument page on top of the user space.
	 * The first four bytes are used to store argc, and the array of string pointers
	 * follow right after. The strings themselves are placed after the array of pointers.
	 */
	argc = *((int *) args);

	/* Just give the beginning of the array of pointers */
	argv = (char **) (args + 4);

	__environ  = argv + argc + 1;

	mutex_init();

	return main(argc, argv);

}
