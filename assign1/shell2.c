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
	char **childEnv = (char**) malloc(sizeof(char*)*(numEnv+2));
	int i;
	for(i=0;i<numEnv;i++){
		childEnv[i]=envp[i];
	}
	char shellpath[PATH_MAX+20];
	char *shell[20];

	sprintf(shellpath, "%s/%s",getcwd(shellpath, PATH_MAX), argv[0]+2);
	char shellEnv[PATH_MAX+30];
	sprintf(shellEnv, "%s=%s","SHELL_PATH",shellpath);
	childEnv[i] = (char *)shellEnv;
	childEnv[i+1] = NULL;
	// printf(childEnv[i]);
	// printf("\n");
	while(1){
		printf("> ");
		fgets(name, 100, stdin);
		char *pos;
		pos = strchr(name, '\n');
		*pos = '\0';
		char *args[100];
		char *token = strtok(name," ");
		int i = 0;
		//printf("args list: \n");
		while(token != NULL){
			args[i] = token;
			token = strtok(NULL, " ");
			//printf("%s ", args[i]);
			i++;
		}
		//printf("\n");
		args[i] = (char*) NULL;
		//printf(childEnv[numEnv-1]);
		environ = childEnv;
		int pid = fork();
		//printf("pid %d", pid);
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
