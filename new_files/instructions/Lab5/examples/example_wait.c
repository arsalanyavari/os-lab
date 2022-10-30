#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#define MAXCHILD 5

void task();

int main()
{
	pid_t pid[MAXCHILD];
	
	for(int i=0; i<MAXCHILD; i++) {
		pid[i] = fork();
		if(pid[i] == 0) {
			task();
		}
	}	

	// comment this line and see the Zombies
	while(wait(NULL)>0); // wait till no proccess exists to waiting


	return 0;
}

void task(){
	printf("[%d] start\n",getpid());
	srand(time(NULL)+getpid());
	int r = rand()%8 + 1;
	sleep(r);
	printf("[%d] finished in %d sec\n",getpid(), r);
	exit (0);
}
