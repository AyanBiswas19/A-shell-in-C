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
	process *p=j->first_process;
	while(p){
		p->stopped=0;
		p=p->next;
	}
	kill(-(j->pgid),SIGCONT);
    return EXIT_SUCCESS;
}