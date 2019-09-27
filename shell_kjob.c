#include "header.h"

int shell_kjob(char *args[]){
	int jobno, sig;
	sscanf(args[1],"%d",&jobno);
	sscanf(args[2],"%d",&sig);
	job *j=jhead;
	while(j){
		if(j->no==jobno)
			break;
		j=j->next;
	}
	if(j==NULL){
		printf("Error: No such job exists.\n");
		return EXIT_FAILURE;
	}
	else
		kill(-(j->pgid),sig);
	return EXIT_SUCCESS;
}