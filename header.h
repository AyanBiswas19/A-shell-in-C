#include <dirent.h>
#include <fcntl.h>
#include <grp.h>
#include <pwd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#include "structs.h"

#define INP_BUFFSIZE (1000)
#define MAX_ARG_LENGTH (300)
#define MAX_ARG_NO (50)
#define MAX_COMMANDNAME_LENGTH (100)
#define MAX_COMMAND_NO (50)
#define MAX_COMMAND_LENGTH (300)
#define MAX_PATH_LENGTH (1000)
#define IO_REDIRECTFILE_PATH_LENGTH (1000)

extern pid_t fgpid;
extern job *jhead;

void get_env_data(env_data *E);
void print_promt(env_data E);
void run_shell();
int check_builtin(char *cname, char clist[][MAX_COMMANDNAME_LENGTH]);
int execute(int ctr, char *args[], int bf);
void print_args(char **args);
void get_args(char *line, char **args);
void get_args2(process *p, char *token);
int shell_cd(char *args[]);
int shell_pwd(char *args[]);
int shell_echo(char *args[]);
int shell_ls(char *args[]);
int shell_pinfo(char *args[]);
int exec_extern(char *args[], int bf);
int get_background_flag(char *s);
void handler();
job *insert_job(job *head, job *Job);
job *remove_job(job *head, pid_t pgid);
job *clean_list(job *head);
void update_jnos(job *head);
job *init_job(const char *command, int bflag);
process *get_proclist(job *j);
int job_runner(job *j, char clist[][MAX_COMMANDNAME_LENGTH]);
int job_printer(job *j);
void launch_process(process *p, pid_t pgid, int infile, int outfile, int bflag,
                    char clist[][MAX_COMMANDNAME_LENGTH]);
process *find_process(job *head, pid_t pid);
void update_jobs(job *head);