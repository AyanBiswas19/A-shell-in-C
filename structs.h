
struct env_data {
  char *user_name;
  char *pwd;
  char *hostname;
};
typedef struct env_data env_data;

struct process {
  struct process *next;
  char **argv;
  pid_t pid;
  char completed;
  char stopped;
  int status;
  int infile,outfile,aflag;
};
typedef struct process process;

struct job {
  struct job *next;
  char *command;
  process *first_process;
  pid_t pgid;
  char done;
  int no;
  int bflag;
};
typedef struct job job;