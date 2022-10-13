#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "sys/types.h"
#include "signal.h"
#include "fcntl.h"
#include "sys/wait.h"
#include "sys/stat.h"
#include "string.h"

#define MAX_CHILD 5
#define MAX_TOTAL 100
#define COUNT 256
#define TRUE 1

int inchild = 0, total = 0, pipefd, tmp, n;
char buffer[COUNT];
int childs[MAX_CHILD];

void handler(int signo)
{
    switch(signo)
    {
    case SIGUSR1:
        n = read(pipefd, buffer, COUNT);
        tmp = atoi(buffer);
        printf("\e[1;35m%d captured by parent.\e[0m\n", tmp);
        total += tmp;
        printf("total=%d\n", total);
        if(total >= MAX_TOTAL)
        {
            printf("\e[1;32mfinally total is %d\e[0m\n", total);
            for(int i=0; i<MAX_CHILD; i++)
                kill(childs[i], SIGKILL);
            system("rm -rf .program2.pipe");
            exit(0);
        }
        break;
    }
}

int main(void)
{
    struct sigaction action;
    action.sa_handler = handler;
    action.sa_flags = 0;
    sigaction(SIGUSR1, (struct sigaction *) &action, NULL);

    char *path = ".program2.pipe";
    mkfifo(path, 0777);
    pipefd = open(path, O_RDONLY | O_NONBLOCK);
    bzero(buffer,COUNT);

    for(int i=0; i<MAX_CHILD; i++)
    {
        childs[i] = fork();
        if(childs[i] < 0)
            printf("failed to fork child %d\n", i);
        else if(! childs[i])
        {
            inchild = 1;
            break;
        }
    }

    if(inchild)
    {
        pipefd = open(path, O_WRONLY | O_NONBLOCK);
        srand(getpid());
        while(TRUE)
        {
            int t = rand() % 10;
            sleep(t);
            printf("\e[1;31mchild pid=%d, t=%d\e[0m\n", getpid(), t);
            sprintf(buffer, "%d\n", t);
            write(pipefd, buffer, COUNT);
            kill(getppid(), SIGUSR1);
        }
    }
    else
        while(TRUE);

    return 0;
}
