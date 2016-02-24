/**
  *  CS2106 Assignment 1
	Zheng Weihan(A0097582N)
	Tse Hong Ming(A0148808U)
 **/

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[], char *envp[]){
	int i;
	char *arg = envp[0];
	char *shellenv;
	shellenv = NULL;
	while (envp[i] != NULL){
		printf(envp[i]);
		printf("\n");
		if(strstr(envp[i], "SHELL_PATH") != NULL){
			shellenv = strstr(envp[i], "SHELL_PATH");
		}
		i++;
	}
		if(shellenv != NULL){
		printf("\nSHELL_PATH value is %s\n\n", strstr(shellenv, "=")+1);	
	}else{
		printf("\nSHELL_PATH value is UNKNOWN\n\n");
		}
}
