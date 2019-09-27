#include "header.h"

int shell_overkill(){
	pid_t pgid[100];
	int i=0;
	job *j=jhead;
	while(j){
		if(j->bflag)
			pgid[i++]=j->pgid;
		j=j->next;
	}
	while(i)
		kill(-pgid[--i],SIGKILL);
	return EXIT_SUCCESS;
}