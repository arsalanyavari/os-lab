#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	pid_t pid;
	int inChild = 0;
	pid = fork();
	if (pid==0)
		inChild = 1;

	while(!inChild) {
		printf("this is Parent pid:%d\n", getpid());
		sleep(1);
	}

	while(inChild) {
		printf("this is Child pid:%d\n", getpid());
		sleep(1);
	}

	return 0;
}

