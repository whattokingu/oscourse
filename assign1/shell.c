/**
 *   CS2106 Assignment 1
 *   Zheng Weihan(A0097582N)
 *   Tse Hong Ming(A0148808U)
**/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int main (){
	char name[100];
	while(1){
		printf("> ");
		fgets(name, 100, stdin);
		char *pos;
		pos = strchr(name, '\n');
		*pos = '\0';
		char *args[100];
		char *token = strtok(name," ");
		int i = 0;
		while(token != NULL){
			args[i] = token;
			token = strtok(NULL, " ");
			i++;
		}
		args[i] = (char*) NULL;
		int pid = fork();
		if(pid > 0){
			printf("Loading new process with id %d\n", pid);
			int status;
			waitpid(pid, &status, 0);
			printf("\n");

		}else if(pid == 0){
			printf("> Parent pid: %d\n", getppid());
			int err = execvp(args[0], args);
			if(err < 0){
				printf("Shell error: %s\n", strerror(errno));
				return 1;
			}
		}
	}
}
