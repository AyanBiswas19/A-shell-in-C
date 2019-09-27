#include "header.h"

int shell_fg(char *args[]){
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
	j->bflag=0;
	tcsetpgrp(STDIN_FILENO, j->pgid);
	kill(-(j->pgid),SIGCONT);
	while(!(j->done)) {} // waiting for j;
	if (tcgetpgrp(STDIN_FILENO) != getpgid(0)) {
      if (tcsetpgrp(STDIN_FILENO, getpgid(0)) != 0)
        perror("Unable to regain terminal input control in parent process.");
    }
    jhead = remove_job(jhead,j->pgid);
    return EXIT_SUCCESS;
}