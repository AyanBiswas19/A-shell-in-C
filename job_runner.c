#include "header.h"

int job_runner(job *j, char clist[][MAX_COMMANDNAME_LENGTH]) {
  pid_t pid;
  int bflag = j->bflag;
  process *p;
  int pipes[2], infile = STDIN_FILENO, outfile;
  for (p = j->first_process; p; p = p->next) {
    if (p->next) {
      if (pipe(pipes) < 0) {
        perror("pipe");
      }
      outfile = pipes[1];
    } else
      outfile = STDOUT_FILENO;
    switch (pid = fork()) {
    case -1:
      perror("fork failed");
      return EXIT_FAILURE;
    case 0:
      launch_process(p, j->pgid, infile, outfile, bflag, clist);
      break;
    default:
      p->pid=pid;
        if (infile != STDIN_FILENO)
        close (infile);
      if (outfile != STDOUT_FILENO)
        close (outfile);
      if (p->next)
        infile = pipes[0];
      if (j->pgid == 0)
        j->pgid = pid;
      setpgid(pid, j->pgid);
      // Check if it is already in tc control
      if (!bflag)
        if (tcgetpgrp(STDIN_FILENO) != j->pgid) {
          if (tcsetpgrp(STDIN_FILENO, getpgid(0)) != 0)
            perror(
                "Unable to regain terminal input control in parent process.");
        }
    }
  }
  if (!bflag) {
    while (!(j->done)) {
      //kill(-getpgrp(), SIGTTIN);
    }
    if (tcgetpgrp(STDIN_FILENO) != getpgid(0)) {
      if (tcsetpgrp(STDIN_FILENO, getpgid(0)) != 0)
        perror("Unable to regain terminal input control in parent process.");
    }
    jhead = remove_job(jhead, j->pgid);
  }
  return EXIT_SUCCESS;
}

int job_printer(job *j) {
  process *p = j->first_process;
  while (p) {
    print_args(p->args);
    if (p->infile)
      printf("< %s\n", p->infile);
    if (p->outfile)
      if (p->aflag)
        printf(">> %s\n", p->outfile);
      else
        printf("> %s\n", p->outfile);
    p = p->next;
  }
  return EXIT_SUCCESS;
}