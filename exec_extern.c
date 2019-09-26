#include "header.h"

int exec_extern(char *args[], int bf) {
  pid_t pid;
  int status;
  switch (pid = fork()) {
  case -1:
    perror("fork failed");
    return EXIT_FAILURE;

  case 0:
    setpgid(getpid(), getpid());
    signal(SIGCHLD, SIG_DFL);
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    signal(SIGTSTP, SIG_DFL);
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
    if (bf == 0) {
      if (tcsetpgrp(STDIN_FILENO, getpgid(getpid())) != 0)
        perror("Unable to give foreground proc terminal input control.");
    }
    if (execvp(*args, args) < 0) {
      perror("Unable to execute");
      exit(EXIT_SUCCESS);
    }
    exit(EXIT_SUCCESS);

  default:
    fgpid = pid;

    setpgid(pid, pid);

    tcsetpgrp(STDIN_FILENO, pid);

    if (bf == 0) {
      fgpid = pid;
      while (fgpid != -1) {
        kill(-getpgrp(), SIGTTIN);
      }
    } else {
      fgpid = 0;
    }

    if (tcgetpgrp(STDIN_FILENO) != getpgid(0)) {
      if (tcsetpgrp(STDIN_FILENO, getpgid(0)) != 0)
        perror("Unable to regain terminal input control in parent process.");
    }
  }
  return EXIT_SUCCESS;
}