#include "header.h"

void launch_process(process *p, pid_t pgid, int infile, int outfile, int bflag,
                    char clist[][MAX_COMMANDNAME_LENGTH]) {
  pid_t pid;
  int cno;
  pid = getpid();
  if (pgid == 0)
    pgid = pid;
  setpgid(pid, pgid);
  if (!bflag)
    tcsetpgrp(STDIN_FILENO, pgid);
  signal(SIGCHLD, SIG_DFL);
  signal(SIGINT, SIG_DFL);
  signal(SIGQUIT, SIG_DFL);
  signal(SIGTSTP, SIG_DFL);
  signal(SIGTTIN, SIG_DFL);
  signal(SIGTTOU, SIG_DFL);
  if (p->infile) {
    close(infile);
    infile = open(p->infile, O_RDONLY);
  } else {
    if (infile != STDIN_FILENO) {
      dup2(infile, STDIN_FILENO);
      close(infile);
    }
  }
  if (p->outfile) {
    close(outfile);
    if (p->aflag)
      outfile = open(p->outfile, O_CREAT | O_APPEND);
    else
      outfile = open(p->outfile, O_CREAT | O_WRONLY | O_TRUNC);
  } else {
    if (outfile != STDOUT_FILENO) {
      dup2(outfile, STDOUT_FILENO);
      close(outfile);
    }
  }
  cno = check_builtin(p->args[0], clist);
  if (cno != -1) {
    execute(cno, p->args, bflag);
    exit(EXIT_SUCCESS);
  }
  execvp(p->args[0], p->args);
  perror("Unable to execute");
  exit(EXIT_FAILURE);
}