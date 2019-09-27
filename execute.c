#include "header.h"

int check_builtin(char *cname, char clist[][MAX_COMMANDNAME_LENGTH]) {
  int ctr = -1;
  for (int i = 0; clist[i][0]; i++)
    if (!strcmp(clist[i], cname))
      ctr = i;
  return ctr;
}

int execute(int ctr, char *args[], int bf) {
  // printf("Execute called %s with cno= %d\n, background flag=
  // %d\n",*args,ctr,bf);
  int return_id = EXIT_SUCCESS;
  if (ctr == -1) {
    return_id = exec_extern(args, bf);
  } else {
    switch (ctr) {
    case 0:
      return_id = shell_cd(args);
      break;
    case 1:
      return_id = shell_echo(args);
      break;
    case 2:
      return_id = shell_pwd(args);
      break;
    case 3:
      return_id = shell_ls(args);
      break;
    case 4:
      return_id = shell_pinfo(args);
      break;
    case 5: return_id=shell_setenv(args);
      break;
    case 6: return_id=shell_unsetenv(args);
      break;
    case 7: return_id=shell_jobs();
      break;
    case 8: return_id=shell_kjob(args);
      break;
    case 9: return_id=shell_fg(args);
      break;
    case 10:return_id=shell_bg(args);
      break;
    case 11:return_id=shell_overkill();
      break;
    default:
      printf("Some very strange error occured\n");
      break;
    }
  }
  return return_id;
}