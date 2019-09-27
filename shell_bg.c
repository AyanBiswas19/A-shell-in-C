#include "header.h"
int shell_bg(char *args[]){
	int n;
	sscanf(args[1],"%d",&n);
	job *j=jhead;
	while(j){
		if(j->no==n)
			break;
		j=j->next;
	}
	if(j==NULL){
		printf("Error: No such job exists.\n");
		return EXIT_FAILURE;
	}
	kill(-(j->pgid),SIGCONT);
    return EXIT_SUCCESS;
}