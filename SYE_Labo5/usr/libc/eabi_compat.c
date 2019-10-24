/* eabi_compat.c 
 *
 * Utility functions needed for (some) EABI conformant tool chains.
 * Required to be able to link against libgcc which provides integer division
 * callbacks and other EABI functions' implementation.
 * Taken from U-Boot's arch/arm/lib/eabi_compat.c
 */

int raise (int signum) {
    return 0;
}

/* Dummy function to avoid linker complaints */
void __aeabi_unwind_cpp_pr0(void)
{
};

void __aeabi_unwind_cpp_pr1(void)
{
};
