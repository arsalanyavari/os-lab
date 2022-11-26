/*
this program initializes 2 signal actions, assigns same handler to both actions.
while action1 is handled, SIGUSR2 will be blocked on delivery.
*/

#include <stdio.h>
#include <stdlib.h> // for EXIT_SUCCESS and EXIT_FAILURE
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>


// "handler1" is handler function for action1 and action2, returns void
void handler1(int signo)
{
	switch(signo)
	{
	/* handling SIGUSR1 takes one second
	during this time if SIGUSR2 will be blocked on delivery. */
	case SIGUSR1:
		sleep(1);
		printf("SIGUSR1 received \n");
		break;
	case SIGUSR2:
		printf("SIGUSR2 received \n");
		break;
	}
}

int main()
{
	//initializing sigaction structures, action1 and action2 both use handler1
	struct sigaction action1;
	struct sigaction action2;

	sigset_t set1;		//define signal set named "set1"
	sigemptyset(&set1);	//making set1 empty
	sigaddset(&set1, SIGUSR2);    //adding SIGUSR2 to set1

	action1.sa_handler = handler1;
	action1.sa_mask = set1;
	//set1 includes SIGUSR2, it means if during handling action1
	//SIGUSR2 will be blocked on delivery.
	action1.sa_flags = 0;

	action2.sa_handler = handler1;
	action2.sa_mask = (sigset_t){0};	//no signal has been blocked for action2
	action2.sa_flags = 0;

	//initializng parent process before fork()
	if ( sigaction(SIGUSR1, &action1,NULL) == -1 ) {
		perror("sigaction(1)");
		return EXIT_FAILURE;
	}
	if ( sigaction(SIGUSR2, &action2,NULL) == -1 ) {
		perror("sigaction(2)");
		return EXIT_FAILURE;
	}

	pid_t cpid = fork();
	if (cpid == -1 ){
		perror("fork()");
		return EXIT_FAILURE;
	} else if( cpid == 0) { // inchild
		pid_t parent=getppid();

		//child sends SIGUSR1 and immediately SIGUSR2 to parent every one second
		while(1) {
			kill(parent,SIGUSR1);
			kill(parent,SIGUSR2);
			sleep(1);
		}

		exit(EXIT_SUCCESS);
	}

	// in parent
	while(1)
		pause();

	return 0;
}

