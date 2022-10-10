#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <time.h>

#define MAXCHILD 5
#define COUNT 256
#define TRUE 1

int main(void)
{
    int pid[MAXCHILD];
    int  child_id = -1;
    int inChild = 0;
    int pipe;
    char *path = "1.pipe";
    char buffer[COUNT];
    int value;
    mkfifo(path,0777);

    for(int i = 0; i < MAXCHILD; i++)
    {
        pid[i] = fork();
        if(! pid[i])
        {
            inChild = 1;
            child_id = i;
            break;
        }
    }

    if(inChild)
    {
        printf("child %d starts\n", child_id);
        pipe = open(path, O_RDWR);
        while(TRUE)
        {
            srand(getpid() * time(NULL));
            sleep(rand() % 2 + 2);
            read(pipe, buffer, COUNT);
            value = atoi(buffer);
            printf("child %d pipevalue: %d\n", child_id, value);
            if(value > 0 && value == child_id)
            {
                sprintf(buffer,"%d", value-1);
                write(pipe, buffer, strlen(buffer));
            }
            else if(value == 0){
                write(pipe, buffer, strlen(buffer));
                printf("child %d reach the point\n", child_id);
                close(pipe);
                exit(0);
            }
            else
                write(pipe, buffer, strlen(buffer));
        }
    }

    if(! inChild)
    {
        pipe = open(path, O_WRONLY);
        sprintf(buffer, "%d", MAXCHILD-1);
        write(pipe, buffer, strlen(buffer));
        close(pipe);
        for(int i = 0; i < MAXCHILD; i++)
            waitpid(pid[i], 0, 0);
        printf("The program finished successfully\n");
        system("rm -rf 1.pipe");
        return 0;
    }
}

