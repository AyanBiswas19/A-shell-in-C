#include "header.h"

int shell_echo(char *args[]) {
  for (int i = 1; args[i]; i++)
    printf("%s ", args[i]);
  return EXIT_SUCCESS;
}