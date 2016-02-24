/**
 *   CS2106 Assignment 1
 *   Zheng Weihan (A0097582N)
 *   Tse Hong Ming (A0148808U)
**/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define PATH_MAX 4096

extern char **environ;
int main (int argc, char *argv[], char *envp[]){
	char name[100];
	int numEnv = 0;
	while(envp[numEnv] != NULL){
		numEnv++;
	}
	//alloc new env array with additional slot for SHELL_PATH
	int i;
	int isShellPathSet;
	
	char **childEnv = (char**) malloc(sizeof(char*)*(numEnv+2));
	isShellPathSet = 0;
	//copy old env array to new env array, checking if SHELL_PATH is defined.
	for(i=0;i<numEnv;i++){
		childEnv[i]=envp[i];
		if(strstr(envp[i], "SHELL_PATH") != NULL){
			isShellPathSet = 1;
		}
	}

	char shellEnv[PATH_MAX+30];
	//add SHELL_PATH if it is not defined, define it.
	if(!isShellPathSet){
		char shellpath[PATH_MAX+20];
		char *shell[20];
		sprintf(shellpath, "%s/%s",getcwd(shellpath, PATH_MAX), argv[0]+2);
		sprintf(shellEnv, "%s=%s","SHELL_PATH",shellpath);
		childEnv[i++] = (char *)shellEnv;
	}
	
	childEnv[i] = NULL;
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
		environ = childEnv;
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
