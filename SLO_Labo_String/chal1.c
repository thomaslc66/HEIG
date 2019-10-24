#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef PASSWORD
#define PASSWORD mySecretPassword
#endif

#define STR_(x) #x
#define STR(x) STR_(x)


int main(int argc, char **argv) {
    char password[100];
    char buffer[100];
    setvbuf(stdout, NULL, _IONBF, 0);
    strcpy(password, STR(PASSWORD));
    printf("Login : ");
    scanf("%99s", buffer);
    printf("Trying: ");
    printf(buffer);
    printf("\n");

    printf("[*] password @ 0x%08x = %d 0x%08x\n", &password, password, password );
    printf("[*] buffer @ 0x%08x = %s\n", buffer, buffer);


    if (strcmp(password, buffer) ==  0) {
        printf("Congratulation\n");
        system("cat /flag");
    } else {
        printf("You failed\n");
    }
    return 0;
}

