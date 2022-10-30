#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/time.h>
#include <stdbool.h>

#define MAXCHILD 5
#define TRUE 1

void _sleep(int r)
{
    struct timeval start,stop;
    srand(time(NULL));
    gettimeofday(&start,NULL);
    while (TRUE)
    {
        gettimeofday(&stop,NULL);
        if ( (stop.tv_sec - start.tv_sec) * 1000 + (stop.tv_usec - start.
tv_usec) / 1000 > r * 1000)
            break;
    }
}

// The first step:
void task(int id)
{
    srand(time(NULL)+getpid()); // This is use to generate random based on time and pid; So the result is difference in each time and each proccess.
    int r = rand() % 5 + 1;
    _sleep(r);
    printf("Task %d has been done by child %d in %d seconds\n", id, getpid(), r);
    exit(0);
}

// The second step
int main(void)
{
    pid_t child [MAXCHILD];
    int status = 0;

    for(int i = 0; i < MAXCHILD; i++)
    {
        child[i] = fork();
        if (! child[i]) // If is child
           task(i);
    }

    while(TRUE)
    {
        // The third part
        _sleep(5);
        for (int i = 0; i < MAXCHILD; i++)
            if (waitpid(child[i], &status, 0))
            {
                child[i] = fork();
                if (! child[i]) // If is child
                    task(i);
            }
    }

    return 0;
}
