#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(){
	int pid, status;

	pid = fork();

	if(pid < 0){
		perror("fork error : ");
		exit(0);
	}
	
	if(pid == 0){
		printf("I'm Child\n");
		sleep(10);
		return 2;
	}else{
		printf("Parent : wait(%d)\n", pid);
		waitpid(pid, &status, 0);

		if(WIFEXITED(status)){
			printf("정상종료\n");
			printf("return value %d\n", WEXITSTATUS(status));
		}else if(WIFSIGNALED(status)){
			printf("신호받았음\n");
			printf("signal num : %d\n", WTERMSIG(status));
		}
	}

	exit(0);
}
