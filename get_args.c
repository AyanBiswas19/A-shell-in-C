#include "header.h"

void print_args(char **args) {
  printf("%s\n", "printing args");
  for (int i = 0; args[i]; i++) {
    printf("%s\t|", args[i]);
  }
}

void get_args(char *line, char **args) {
  if (line == NULL) {
    return;
  }
  int i = 0;
  char *token = strtok(line, " ");
  if (!token) {
    *args = NULL;
    return;
  }
  while (token) {
    args[i++] = token;
    token = strtok(NULL, " ");
  }
  args[i] = '\0';
}