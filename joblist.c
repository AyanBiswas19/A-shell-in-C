#include "header.h"

job *insert_job(job *head, job *Job){
	job *j=head;
	if(!j){
		Job->no=1;
		return Job;
	}
	int i=1;
	while(j->next){
		j=j->next;
	}
	j->next=Job;
	update_jnos(head);
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
	update_jnos(head);
	return head;
}

void update_jnos(job *head){
	int i=1;
	while(head){
		head->no=i++;
		head=head->next;
	}
}