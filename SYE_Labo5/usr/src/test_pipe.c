#include <stdlib.h>
#include <syscall.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>


void affiche(char* processus ,char* buffer, size_t size){
	char new_buffer[size];

	for(size_t i = 0; i < size; i++){
		new_buffer[i] = buffer[i];
		printf("%s %s\n", processus, new_buffer);
	}
}

int main(int argv, char **argc){

	int pid;
	int fd_pere_fils[2];
	int fd_fils_pere[2];
	size_t length;


	if(argv > 1){
		length = strlen(argc[1]);
	}


	if(pipe(fd_pere_fils) != 0){
		printf("error on pipe pere fils\n");
	}


	if(pipe(fd_fils_pere) != 0){
		printf("error on pipe fils pere\n");
	}


	char* buffer = argc[1];
	char  buffer_message[length];

	pid = fork(); //creation du nouveau processus

	if(pid == 0){ //dans le fils

		printf("Dans le fils\n");
		close(fd_pere_fils[0]);
		sys_write(fd_pere_fils[1], (const void*) &buffer, length);
		close(fd_pere_fils[1]);


		exit(0);

	}else{ // dans le parentl
		printf("Dans le père\n");
		close(fd_pere_fils[1]);
		int count =  sys_read(fd_pere_fils[0], (void*) &buffer_message, length);
		close(fd_pere_fils[0]);			
		printf("%d\n", count);
		printf("%s\n", buffer_message);

		waitpid(pid,NULL,0);
	}
	exit(0);
}


