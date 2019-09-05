#include "header.h"

job *insert_job(job *head, job *Job){
	job *j=head;
	if(!j){
		Job->next=NULL;
		return Job;
	}
	while(j->next){
		j=j->next;
	}
	j->next=Job;
	return head;
}

job *remove_job(job *head, pid_t pgid){
	job *j=head;
	if(j->pgid==pgid){
		j=j->next;
		free(head);
		return j;
	}
	while(j->next){
		if(j->next->pgid==pgid){
			job *t=j->next;
			j->next=j->next->next;
			free(t);
			break;
		}
	}
	return head;
}