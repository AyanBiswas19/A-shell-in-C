#include "header.h"

int shell_echo(char *args[]) {
  for (int i = 1; args[i]; i++)
    printf("%s ", args[i]);
  printf("\n");
  return EXIT_SUCCESS;
}
