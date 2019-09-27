#include "header.h"

void print_promt(env_data E) {
  printf("<%s@%s:%s>", E.user_name, E.hostname, E.pwd);
}

int get_background_flag(char *s) {
  int i;
  for (i = strlen(s) - 1; s[i] == ' '; i--)
    ;
  if (s[i] == '&') {
    s[i] = '\0';
    return 1;
  }
  return 0;
}

void run_shell() {
  int i;
  env_data E;
  E.pwd = malloc(MAX_PATH_LENGTH * sizeof(char));
  char clist[][MAX_COMMANDNAME_LENGTH] = {
      "cd",   "echo", "pwd", "ls", "pinfo",    "setenv", "unsetenv",
      "jobs", "kjob", "fg",  "bg", "overkill", "\0"};
  char inp_line[INP_BUFFSIZE * sizeof(char)],
      cname[MAX_COMMANDNAME_LENGTH * sizeof(char)], *command, *param;
  char *args[MAX_ARG_NO * sizeof(char *)];
  char *commands[MAX_COMMAND_NO * sizeof(char *)];
  int background_flags[MAX_COMMAND_NO * sizeof(int)];
  inp_line[0] = '\0';
  int exit_flag = 0, cno, rid;
  while (1) {
    get_env_data(&E);
    fflush(stdout);
    print_promt(E);
    if (fgets(inp_line, INP_BUFFSIZE, stdin) == NULL) {
      printf("\n");
      return;
    }
    inp_line[strlen(inp_line) - 1] = '\0';
    if (strlen(inp_line) == 0) {
      continue;
    }
    i = 0;
    command = strtok(inp_line, ";");
    while (command) {
      commands[i] = command;
      background_flags[i] = get_background_flag(command);
      i++;
      command = strtok(NULL, ";");
    }
    commands[i] = NULL;

    for (i = 0; commands[i]; i++) {
      if (!strncmp(commands[i], "quit", 4)) {
        exit_flag = 1;
        break;
      }
      job *j = init_job(commands[i], background_flags[i]);
      jhead = insert_job(jhead, j);
      update_jnos(jhead);
      rid = job_runner(j, clist);
    }

    // for (i = 0; commands[i]; i++) {
    //   get_args(commands[i], args);
    //   if (!*args) continue;
    //   if (!strcmp(args[0], "exit")) {
    //     exit_flag = 1;
    //     break;
    //   }
    //   // Check if command is built in
    //   cno = check_builtin(args[0], clist);
    //   // Execute it
    //   rid = execute(cno, args, background_flags[i]);
    //   // Check exit status of execute maybe?
    // }
    printf("\n");
    if (exit_flag)
      break;
  }
  free(E.pwd);
}