#include "header.h"

int check_builtin_nopipe(job *j, char clist[][MAX_COMMANDNAME_LENGTH]){
	process *p=j->first_process;
	if(p==NULL)
		return 30;
	if(p->next)
		return 31;
	int cno=check_builtin(p->args[0],clist);
	return cno;
}

int isDoneOrStopped(job *j){
	int flag=1;
	if(j==NULL)
		return 1;
	process *p=j->first_process;
	while(p){
		if(!(p->done || p->stopped)){
			flag=0;
			break;
		}
		p=p->next;
	}
	if(!(j->done) && flag){
		j->stopped=1;
		j->bflag=1;
	}
	return flag;
}

int job_runner(job *j, char clist[][MAX_COMMANDNAME_LENGTH]) {
  pid_t pid;
  int bflag = j->bflag;
  process *p=j->first_process;
  int t=check_builtin_nopipe(j,clist);
  if(t==30)
  	return 0;
  if(t>=0 && t<30 && !bflag){
  	int s_infile=dup(STDIN_FILENO);
  	int s_outfile=dup(STDOUT_FILENO);
  	int infile=STDIN_FILENO;
  	int outfile=STDOUT_FILENO;
  	if(p->infile){
  		infile=open(p->infile,O_RDONLY,0777);
  	}
  	if(infile!=STDIN_FILENO){
  		dup2(infile,STDIN_FILENO);
  	}
  	if(p->outfile){
  		if(p->aflag){
  	 		outfile=open(p->outfile, O_CREAT | O_APPEND, 0777);
  	 	}
  	 	else{
  	 		outfile=open(p->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0777);
  	 	}
  	}
  	if(outfile!=STDOUT_FILENO){
  		dup2(outfile,STDOUT_FILENO);
  	}
  	execute(t,p->args,bflag);
  	//cleanup
  	if(s_infile!=STDIN_FILENO)
  		dup2(s_infile,STDIN_FILENO);
  	if(s_outfile!=STDOUT_FILENO)
  		dup2(s_outfile,STDOUT_FILENO);
  	close(s_infile);
 	close(s_outfile);
 	jhead=remove_job(jhead,0);
  	return EXIT_SUCCESS;
  }
  j->running=1;
  int pipes[2], infile = STDIN_FILENO, outfile;
  for (p = j->first_process; p; p = p->next) {
    if (p->next) {
      if (pipe(pipes) < 0) {
        perror("pipe");
      }
      outfile = pipes[1];
    } else
      outfile = STDOUT_FILENO;
    switch (pid = fork()) {
    case -1:
      perror("fork failed");
      return EXIT_FAILURE;
    case 0:
      launch_process(p, j->pgid, infile, outfile, bflag, clist);
      break;
    default:
      p->pid = pid;
      if (infile != STDIN_FILENO)
        close(infile);
      if (outfile != STDOUT_FILENO)
        close(outfile);
      if (p->next)
        infile = pipes[0];
      if (j->pgid == 0)
        j->pgid = pid;
      setpgid(pid, j->pgid);
      // Check if it is already in tc control
      if (!bflag)
        if (tcgetpgrp(STDIN_FILENO) != j->pgid) {
          if (tcsetpgrp(STDIN_FILENO, getpgid(0)) != 0)
            perror(
                "Unable to regain terminal input control in parent process.");
        }
    }
  }
  if (!bflag) {
    while (!isDoneOrStopped(j)) {
      // kill(-getpgrp(), SIGTTIN);
    }
    if (tcgetpgrp(STDIN_FILENO) != getpgid(0)) {
      if (tcsetpgrp(STDIN_FILENO, getpgid(0)) != 0)
        perror("Unable to regain terminal input control in parent process.");
    }
    if(j->done)
    	jhead = remove_job(jhead, j->pgid);
  }
  return EXIT_SUCCESS;
}

int job_printer(job *j) {
  process *p = j->first_process;
  while (p) {
    print_args(p->args);
    if (p->infile)
      printf("< %s\n", p->infile);
    if (p->outfile)
      if (p->aflag)
        printf(">> %s\n", p->outfile);
      else
        printf("> %s\n", p->outfile);
    p = p->next;
  }
  return EXIT_SUCCESS;
}