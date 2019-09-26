#include "header.h"

int shell_ls(char *args[]) {
  int a_flag = 0, l_flag = 0, only_flags_flag = 1;
  for (int i = 1; args[i]; i++) {
    if (args[i][0] == '-') {
      for (int j = 1; args[i][j]; j++) {
        if (args[i][j] == 'a')
          a_flag++;
        if (args[i][j] == 'l')
          l_flag++;
      }
    } else
      only_flags_flag = 0;
  }
  if (only_flags_flag) {
    DIR *dp = opendir(".");
    if (!dp) {
      printf("unable open cwd.");
      return EXIT_SUCCESS;
    }
    struct dirent *d;
    while (d = readdir(dp)) {
      if (d->d_name[0] == '.') // terrible way to work with a_flag
        if (!a_flag)
          continue;
      if (l_flag) // time for long listing....
      {
        char months[12][50] = {"Jan", "Feb", "Mar", "April", "May", "Jun",
                               "Jul", "Aug", "Sep", "Oct",   "Nov", "Dec"};
        struct stat status;
        if (stat(d->d_name, &status)) {
          printf("Unable to retrieve status of: %s\n", d->d_name);
          continue;
        }
        printf(S_ISDIR(status.st_mode) ? "d" : "-");
        printf((status.st_mode & S_IRUSR) ? "r" : "-");
        printf((status.st_mode & S_IWUSR) ? "w" : "-");
        printf((status.st_mode & S_IXUSR) ? "x" : "-");
        printf((status.st_mode & S_IRGRP) ? "r" : "-");
        printf((status.st_mode & S_IWGRP) ? "w" : "-");
        printf((status.st_mode & S_IXGRP) ? "x" : "-");
        printf((status.st_mode & S_IROTH) ? "r" : "-");
        printf((status.st_mode & S_IWOTH) ? "w" : "-");
        printf((status.st_mode & S_IXOTH) ? "x" : "-");
        printf("\t%u\t", (unsigned int)status.st_nlink);
        struct passwd *p;
        struct group *g;
        p = getpwuid(status.st_uid);
        printf("%s\t", p->pw_name);
        g = getgrgid(status.st_gid);
        printf("%s\t", g->gr_name);
        printf("%zu\t", status.st_size);
        struct tm *t = localtime(&status.st_mtime);
        printf("%s\t%d\t%d:%d\t", months[t->tm_mon], t->tm_mday, t->tm_hour,
               t->tm_min);
      }
      printf("%s\n", d->d_name);
    }
  } else {
    struct stat status;
    for (int i = 1; args[i]; i++) {
      if (args[i][0] != '-') {
        if (stat(args[i], &status))
          continue;
        else {
          if (S_ISDIR(status.st_mode)) {
            DIR *dp = opendir(args[i]);
            if (!dp) {
              printf("Unable open %s\n", args[i]);
              return EXIT_SUCCESS;
            }
            struct dirent *d;
            while (d = readdir(dp)) {
              if (d->d_name[0] == '.') // terrible way to work with a_flag
                if (!a_flag)
                  continue;
              if (l_flag) // time for long listing....
              {
                char months[12][50] = {"Jan", "Feb", "Mar", "April",
                                       "May", "Jun", "Jul", "Aug",
                                       "Sep", "Oct", "Nov", "Dec"};
                if (stat(d->d_name, &status)) {
                  printf("Unable to retrieve status of: %s\n", d->d_name);
                  continue;
                }
                printf(S_ISDIR(status.st_mode) ? "d" : "-");
                printf((status.st_mode & S_IRUSR) ? "r" : "-");
                printf((status.st_mode & S_IWUSR) ? "w" : "-");
                printf((status.st_mode & S_IXUSR) ? "x" : "-");
                printf((status.st_mode & S_IRGRP) ? "r" : "-");
                printf((status.st_mode & S_IWGRP) ? "w" : "-");
                printf((status.st_mode & S_IXGRP) ? "x" : "-");
                printf((status.st_mode & S_IROTH) ? "r" : "-");
                printf((status.st_mode & S_IWOTH) ? "w" : "-");
                printf((status.st_mode & S_IXOTH) ? "x" : "-");
                printf("\t%u\t", (unsigned int)status.st_nlink);
                struct passwd *p;
                struct group *g;
                p = getpwuid(status.st_uid);
                printf("%s\t", p->pw_name);
                g = getgrgid(status.st_gid);
                printf("%s\t", g->gr_name);
                printf("%zu\t", status.st_size);
                struct tm *t = localtime(&status.st_mtime);
                printf("%s\t%d\t%d:%d\t", months[t->tm_mon], t->tm_mday,
                       t->tm_hour, t->tm_min);
              }
              printf("%s\n", d->d_name);
            }
          }
        }
      }
    }
  }
  return EXIT_SUCCESS;
}