#include "header.h"

int shell_pinfo(char *args[]) {
  char proc_stat_path[200];
  char proc_exec_path[300];
  char buff[2000];
  printf("Entering pinfo\n");
  pid_t pid = 0;
  if (args[1]) {
    sscanf(args[1], "%d", &pid);
  } else
    pid = getpid();
  sprintf(proc_stat_path, "/proc/%ld/status", (long)pid);
  printf("pid -- %ld\n", (long)pid);
  int fd = open(proc_stat_path, O_RDONLY);
  if (fd == -1) {
    perror("Unable to open status file");
    return EXIT_SUCCESS;
  }
  read(fd, buff, 2000);
  for (char *i = strstr(buff, "State"); *i != '\n'; i++)
    printf("%c", *i);
  printf("\n");
  for (char *i = strstr(buff, "VmSize"); *i != '\n'; i++)
    printf("%c", *i);
  printf("\n");
  proc_stat_path[0] = '\0';
  sprintf(proc_stat_path, "/proc/%ld/exe", (long)pid);
  readlink(proc_stat_path, proc_exec_path, 300);
  printf("Executable path: %s", proc_exec_path);
  close(fd);
  return EXIT_SUCCESS;
}