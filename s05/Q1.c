#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define COUNT 256
#define MAX_CHILD 5
#define MAXIMUM 100
#define t 2

int main(void)
{
    int fd[MAX_CHILD][2];
    pid_t pid[MAX_CHILD];
    int inchild = 0;
    int total = 0;
    int id = 0;
    char buffer[COUNT];
    for (id = 0; id < MAX_CHILD; id++)
    {
        pipe(fd[id]);
        pid[id] = fork();
        if (! pid[id])
        {
            inchild = 1;
            close(fd[id][0]);
            break;
        }
        else
            close(fd[id][1]);
    }
    while (inchild)
    {
        srand(getpid());
        int random = rand()%10;
        sprintf(buffer,"%d",random);
        write(fd[id][1], buffer, 255);
        sleep(t);
    }
    while (! inchild)
    {
        for(int i = 0; i < MAX_CHILD; i++)
            if(read(fd[i][0], buffer, 255) > 0)
            {
                total += atoi(buffer);
                printf("Total is: %d\n", total);
                if(total >= MAXIMUM)
                {
                    for(int k = 0; k < MAX_CHILD; k++)
                        kill(pid[k], SIGKILL);
                    exit(0);
                }
            }

    }
}
