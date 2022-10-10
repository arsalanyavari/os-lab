#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TRUE 1

int main()
{
    while(TRUE)
    {
        sleep(2);
        pid_t pid = fork();
        if(! pid)
        {
            printf("Child! Pid is %d\n", getpid());
            exit(0);
        }
    }
    return 0;
}
