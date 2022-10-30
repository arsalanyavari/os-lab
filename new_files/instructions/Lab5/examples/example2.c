#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXCHILD 5

void task();

int main()
{
	pid_t child[MAXCHILD];
	int status=0;
	
	for( int i=0; i<MAXCHILD; i++) {
		child[i] = fork();
		if( child[i]==0)
			task(); // done by child
	}
	
	// in Parent
	int child_d;
	while(1) {
		sleep(1);
		for( int i=0; i<MAXCHILD; i++) {
			// ** comment form here
			/*
			child_d = wait(&status);

			if ( child_d>0 )
				printf("child[%d] is dead now \n", child_d);
			else if( child_d==-1)
				printf("no child to wait for \n");
				*/
			// ** comment till this line

			// *** uncomment form here
			child_d = waitpid(child[i], &status, 0);
			if(child_d==0)
				printf("child[%d] is still alive\n", child[i]);
			else if(child_d>0)
			 	printf("child[%d] is dead now\n", child[i]);
			else
			 	printf("no specific child to wait for \n");
			// *** to here
		}
	}	
	return 0;
}

void task(){
	srand(getpid());
	int r = rand()%5 +1;
	printf("message form child %d: sleeping %d seconds\n", getpid(), r);
	sleep(r);
	exit (0);
}
