#include "header.h"

void handler() {
  while (1) {
    int status;
    pid_t pid = waitpid(-1, &status, WNOHANG | WUNTRACED);
    // printf("%ld\n",(long)pid );
    // printf("%ld\n",(long)fgpid );
    if (pid == -1) {
      // perror("handler -1 case");
      return;
    }
    if (pid == 0) {
      // No child proccesses running
      return;
    }
    if (pid > 0) {
      process *p = find_process(jhead, pid);
      if (p)
        p->done = 1;
      jhead = update_jobs(jhead);
      // return;
    } else
      fprintf(stderr, "Process pid: %ld exited successfully.\n", (long)pid);
  }
}