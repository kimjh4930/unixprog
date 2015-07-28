#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	pid_t pid;

	if((pid = fork()) < 0){
		printf("fork error\n");
		exit(0);
	}else if(pid == 0){
		if((pid = fork()) < 0){
			printf("fork error\n");
			exit(0);
		}else if(pid > 0){
			printf("first child pid = %ld\n", (long)getpid());
			exit(0);
		}else{

			sleep(10);
			printf("second child pid = %ld\n", (long)getpid());
			printf("second child, parent pid = %ld\n", (long)getppid());
		}
	}else{
		printf("parent pid = %ld\n", (long)getpid());
//		sleep(2);
		if(waitpid(pid, NULL, 0) != pid ){
			printf("waitpid error");
		}
	}

	exit(0);
}
