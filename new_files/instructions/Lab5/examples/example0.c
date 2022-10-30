#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
void task();

int main()
{
	pid_t pid;
	
	while(1) {
		pid = fork();
		if(pid == 0) {
			task();
		}
		sleep(2);
	}	
	return 0;
}

void task(){
	printf("%d\n",getpid());
	exit (0);
}
