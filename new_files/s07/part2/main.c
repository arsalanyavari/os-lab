#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/time.h>

#define TRUE 1

void handler1(int signo)
{
    if( signo == SIGALRM )
        printf("SIGALARM received \n");
}

int main(void)
{
    struct sigaction act;
    act.sa_handler = handler1;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    if ( sigaction(SIGALRM, &act,NULL) == -1 )
    {
        perror("sigaction(2)");
        return EXIT_FAILURE;
    }

    alarm(5);

    while(TRUE)
        printf("I am alive!\n") && sleep(1);

    return 0;
}
