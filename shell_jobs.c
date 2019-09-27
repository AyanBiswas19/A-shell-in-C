#include "header.h"

int shell_jobs(){
	job *j=jhead;
	while(j){
		if(!(j->running)){
			j=j->next;
			continue;
		}		
    	printf("\n[%d] ", j->no);
		if(j->stopped)
			printf("Stopped");
		else
			printf("Running");
		printf(" '%s' with pgid %d.", j->argspace, (int)(j->pgid));
		j=j->next;
	}
	return EXIT_SUCCESS;
}