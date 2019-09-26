#include "header.h"

void print_args(char **args) {
  printf("%s\n", "printing args");
  for (int i = 0; args[i]; i++) {
    printf("%s\t$\n", args[i]);
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

void get_args2(process *p, char *token) {
  char *line = strdup(token);
  char *tok;
  int i = 0;
  while (tok = strsep(&line, " ")) {
    if (*tok == '\0')
      continue;
    if (tok[0] != '<' && tok[0] != '>') {
      p->args[i++] = tok;
      continue;
    }
    if (tok[0] == '<') {
      if (tok[1])
        p->infile = strdup(tok + 1);
      else {
        tok[0] = ' ';
        tok = strsep(&line, " ");
        p->infile = strdup(tok);
      }
      continue;
    }
    if (tok[0] == '>') {
      if (tok[1] == '>') {
        p->aflag = 1;
        if (tok[2])
          p->outfile = strdup(tok + 2);
        else {
          tok = strsep(&line, " ");
          p->outfile = strdup(tok);
        }
      } else {
        p->aflag = 0;
        if (tok[1])
          p->outfile = strdup(tok + 1);
        else {
          tok = strsep(&line, " ");
          p->outfile = strdup(tok);
        }
      }
      continue;
    }
  }
}