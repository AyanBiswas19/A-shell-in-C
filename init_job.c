#include "header.h"

job *init_job(const char *command, int bflag){
	job *j=malloc(sizeof(job));
	j->next=NULL;
	j->command=malloc((strlen(command)+1)*sizeof(char));
	char *temp=malloc((strlen(command)+1)*sizeof(char));
	strcpy(j->command,command);
	strcpy(temp,command);
	j->first_process=get_proclist(j);
	strcpy(j->command,temp);
	free(temp);
	j->pgid=0;
	j->done=0;
	j->no=0;
	j->bflag=bflag;
	return j;
}

process *get_proclist(job *j){
	char *s=j->command, *token;
	process *p=NULL,*h=NULL;
	while(token=strtok(NULL,"|")){
		if(p){
			p->next=malloc(sizeof(process));
			p=p->next;
		}
		else{
			p=malloc(sizeof(process));
			h=p;
		}
		p->next=NULL;
		p->pid=0;
		p->completed=0;
		p->stopped=0;
		p->status=0;
	}
	return h;
}