#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#define COUNT 256
#define MAX_CHILD 5
#define MAXIMUM 100

int main(void)
{
    int fd[2];
    pid_t pid[MAX_CHILD];
    int inchild = 0, total = 0, id = 0;
    char buffer[COUNT];
    pipe(fd);
    for (id = 0; id < MAX_CHILD; id++)
    {
        pid[id] = fork();
        if (pid[id] == 0)
        {
            inchild = 1;
            break;
        }
    }
    while (inchild)
    {
        srand(time(NULL) + getpid());
        int random = rand()%5;
        sleep(random);
        sprintf(buffer,"%d",random);
        close(fd[0]);
        write(fd[1], buffer, 255);
    }
    while (! inchild)
    {
        close(fd[1]);
        if(read(fd[0], buffer, 255) > 0)
        {
            total += atoi(buffer);
            memset(buffer,0,strlen(buffer));
            printf("Total is: %d\n", total);
            if(total >= MAXIMUM)
            {
                for(int k = 0; k < MAX_CHILD; k++)
                    kill(pid[k], SIGKILL);
                exit(0);
            }
        }
    }
    return 0;
}
