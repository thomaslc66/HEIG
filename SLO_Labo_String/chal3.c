#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define STR_(x) #x
#define STR(x) STR_(x)

#ifndef SEED
#define SEED 64
#endif


void fail() {
    printf("You failed \n");
    exit(0);
}

void win() {
    printf("WIN\n");
    system("cat /flag");
}

int main(int argc, char **argv) {
    void (*function)();
    char buffer[SEED];
    setvbuf(stdout, NULL, _IONBF, 0);
    function = fail;
    printf("Login : ");
    scanf("%" STR(SEED) "s", buffer);
    printf(buffer);
    printf("\n");
    printf("Password :");
    scanf("%" STR(SEED) "s", buffer);
    printf(buffer);
    function();
    return 0;
}
