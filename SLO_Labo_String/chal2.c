#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define STR_(x) #x
#define STR(x) STR_(x)

#ifndef SEED
#define SEED 64
#endif

void (*function)();
char buffer[SEED];

void fail() {
    printf("You failed \n");
}

void win() {
    printf("WIN\n");
    system("cat /flag");
}

int main(int argc, char **argv) {
    setvbuf(stdout, NULL, _IONBF, 0);
    char input[SEED];

    function = fail;

    printf("Input : ");

    scanf("%" STR(SEED) "s", buffer);
    strncpy(input, buffer, SEED);

    printf(input);
    printf("\n");
    function();
    return 0;
}

