
struct env_data {
  char *user_name;
  char *pwd;
  char *hostname;
};
typedef struct env_data env_data;

struct process {
  struct process *next;
  char **args;
  pid_t pid;
  char completed;
  char stopped;
  int done;
  char *infile, *outfile;
  int aflag;
};
typedef struct process process;

struct job {
  struct job *next;
  char *command;
  char *argspace;
  process *first_process;
  pid_t pgid;
  char done;
  int no;
  int bflag;
};
typedef struct job job;