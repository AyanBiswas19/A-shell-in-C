#include "header.h"

int shell_setenv(char *args[]){
	if(args[3] || !args[1]){
		printf("Invalid syntax\n");
		return EXIT_SUCCESS;
	}
	if(setenv(args[1],args[2],0)==-1)
		perror("Cannot set");
	return EXIT_SUCCESS;
}

int shell_unsetenv(char *args[]){
	if(!args[1]){
		printf("Invalid syntax\n");
		return EXIT_SUCCESS;
	}
	if(unsetenv(args[1])==-1)
		perror("Cannot unset");
	return EXIT_SUCCESS;
}