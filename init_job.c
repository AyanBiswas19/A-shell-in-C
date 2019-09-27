#include "header.h"

job *init_job(const char *command, int bflag) {
  job *j = malloc(sizeof(job));
  j->next = NULL;
  j->command = strdup(command);
  j->argspace = strdup(command);
  j->first_process = get_proclist(j);
  j->pgid = 0;
  j->done = 0;
  j->no = 0;
  j->bflag = bflag;
  return j;
}

process *get_proclist(job *j) {
  char *s = j->argspace, *token;
  process *p = NULL, *h = NULL;
  while (token = strsep(&(j->command), "|")) {
    if (*token == '\0') {
      continue;
    } // strsep seems to have null if delimeters are in the form dd
    if (p) {
      p->next = malloc(sizeof(process));
      p = p->next;
    } else {
      p = malloc(sizeof(process));
      h = p;
    }
    p->next = NULL;
    p->pid = 0;
    p->completed = 0;
    p->stopped = 0;
    p->aflag = 0;
    p->done = 0;
    p->args = malloc(MAX_ARG_NO * sizeof(char *));
    get_args2(p, token);
  }
  return h;
}
