#include "header.h"

pid_t fgpid = -1;
job *jhead = NULL;

int main() {
  // fgpid=0;
  setpgid(0, getpid());
  signal(SIGCHLD, handler);
  //signal(SIGINT, SIG_IGN);
  //signal(SIGQUIT, SIG_IGN);
  signal(SIGTSTP, SIG_IGN);
  signal(SIGTTIN, SIG_IGN);
  signal(SIGTTOU, SIG_IGN);
  tcsetpgrp(STDIN_FILENO, getpgrp());
  // Load configuration
  // Run the loop
  run_shell();
  // Cleanup
  return 0;
}