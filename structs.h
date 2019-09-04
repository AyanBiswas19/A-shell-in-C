
struct env_data {
  char *user_name;
  char *pwd;
  char *hostname;
};
typedef struct env_data env_data;

struct process {
  struct process *next; /* next process in pipeline */
  char **argv;          /* for exec */
  pid_t pid;            /* process ID */
  char completed;       /* true if process has completed */
  char stopped;         /* true if process has stopped */
  int status;           /* reported status value */
};
typedef struct process process;

struct job {
  struct job *next;          /* next active job */
  char *command;             /* command line, used for messages */
  process *first_process;    /* list of processes in this job */
  pid_t pgid;                /* process group ID */
  char notified;             /* true if user told about stopped job */
  struct termios tmodes;     /* saved terminal modes */
  int stdin, stdout, stderr; /* standard i/o channels */
};
typedef struct job job;