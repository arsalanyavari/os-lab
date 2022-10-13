#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/time.h>
#include <stdbool.h>

#define MAXCHILD 10
#define TRUE 1

void _sleep(int r)
{
    struct timeval start,stop;
    srand(time(NULL));
    gettimeofday(&start,NULL);
    while (TRUE)
    {
        gettimeofday(&stop,NULL);
        if ( (stop.tv_sec - start.tv_sec) * 1000 + (stop.tv_usec - start.tv_usec) / 1000 > r * 1000)
            break;
    }
}

void killChild(void)
{
    srand(getpid());
    int r = rand() % 1000 + 1;
    _sleep(r);
    printf("child %d, %d seconds waited\n", getpid(), r);
    exit(0);
}


int main(void)
{
    pid_t child [MAXCHILD];
    bool inChild = 0;
    int status = 0;
    for(int i = 0; i < MAXCHILD; i++)
    {
        child[i] = fork();
        if (! child[i])
        {
            inChild = 1;
            break;
        }
    }

    while(! inChild)
    {
        _sleep(5);
        for (int i = 0; i < MAXCHILD; i++)
            if (wait(&status))
            {
                child[i] = fork();
                if (! child[i])
                {
                    inChild = 1;
                    break;
                }
            }
    }

    if (inChild)
        killChild();
    return 0;
}
