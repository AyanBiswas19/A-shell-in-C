#include "header.h"

job *insert_job(job *head, job *Job) {
  job *j = head;
  if (!j) {
    Job->no = 1;
    return Job;
  }
  int i = 1;
  while (j->next) {
    j = j->next;
  }
  j->next = Job;
  update_jnos(head);
  return head;
}

job *remove_job(job *head, pid_t pgid) {
  job *j = head;
  if (j->pgid == pgid) {
    j = j->next;
    free(head);
    return j;
  }
  while (j->next) {
    if (j->next->pgid == pgid) {
      job *t = j->next;
      j->next = j->next->next;
      free(t);
      break;
    }
    j = j->next;
  }
  update_jnos(head);
  return head;
}

void update_jnos(job *head) {
  int i = 1;
  while (head) {
    head->no = i++;
    head = head->next;
  }
}

job *clean_list(job *head) {
  job *p = head;
  while (p) {
    if (p->done && p->bflag) {
      printf("Background job: %s exited with pgid %d.\n", p->command, p->pgid);
      head = remove_job(head, p->pgid);
    }
    p = p->next;
  }
  return head;
}

process *find_process(job *head, pid_t pid) {
  job *j = head;
  while (j) {
    process *p = j->first_process;
    while (p) {
      if (p->pid == pid)
        return p;
      p = p->next;
    }
    j = j->next;
  }
  return NULL;
}

job *update_jobs(job *head) {
  job *j = head;
  process *p;
  while (j) {
    p = j->first_process;
    j->done = 1;
    while (p) {
      if (p->done != 1) {
        j->done = 0;
        break;
      }
      p = p->next;
    }
    j = j->next;
  }
  head = clean_list(head);
  return head;
}