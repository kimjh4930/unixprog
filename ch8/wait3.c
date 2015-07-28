#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>

#define FALSE 0
#define TRUE 1

int done = FALSE;

void reaper(int sig){
	int status;
	struct rusage usage;
	pid_t pid2 = wait3(&status, 0, &usage);

	printf("... child of %d done calling cat. \n", getpid());
	printf("exit code for %d is %d\n", pid2, status);

	done = TRUE;
}

void main(){
	pid_t pid1;
	int status;
	struct rusage usage;

	signal(SIGCHLD, reaper);

	if((pid1 = fork())){
		printf("I'm Parent %d; child is %d\n", getpid(), pid1);
	}else{
		printf("Child %d : waiting 5 seconds. \n",getpid());
		sleep(5);
		printf("child %d : calling cat...\n", getpid());
		execl("/bin/ls","ls", "-al", NULL);
		printf("we should never get here!\n");
	}

	printf("there's life after forking!\n");
	while(!done){
		printf("doing something...\n");
		sleep(1);
	}

	printf("got my SIGCHLD, cleaning up!\n");
	signal(SIGCHLD,SIG_DFL);
}
