#include "header.h"

int shell_pwd(char *args[]) {
  char path[MAX_PATH_LENGTH];
  getcwd(path, MAX_PATH_LENGTH);
  printf("%s\n", path);
  return EXIT_SUCCESS;
}