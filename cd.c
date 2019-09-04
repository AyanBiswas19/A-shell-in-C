#include "header.h"

int shell_cd(char *args[]) {
  if (chdir(args[1]) == -1) {
    perror("CD has failed");
    return EXIT_SUCCESS;
  }
  if (args[2]) {
    printf("Directory is changed but additional arguments provided are not "
           "accounted for nor checked.\n");
  }
  return EXIT_SUCCESS;
}