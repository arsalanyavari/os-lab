#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#define ARRAY_SIZE 100
#define MAX_CHILD 5
#define TRUE 1

u_int8_t _do = 0;

void handler(int signum)
{
    printf("Child recive SIG(%d)\n", signum);
    if( signum == SIGUSR1 )
		_do = 1;
}

void task(int chId, int *data)
{
    printf("child %d is running....\n", chId);
    while(TRUE)
    {
        pause();
		if ( _do )
        {
			for(int i=chId; i<ARRAY_SIZE; i+=MAX_CHILD)
				data[i] = 2*data[i]+ 1;
			break;
		}
    }
    exit(EXIT_SUCCESS);
}

int main(void)
{
    struct sigaction act;
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    sigaction(SIGUSR1, &act, NULL);

    // set shared memory
    int size = ARRAY_SIZE * sizeof(int);
    int *data = (int *)mmap(0, size, PROT_READ | PROT_WRITE,
                            MAP_SHARED | MAP_ANONYMOUS, 0, 0);

    if (data == (void *)-1)
    {
        perror("mmap()");
        return EXIT_FAILURE;
    }

    // create childs
    pid_t childs[MAX_CHILD];

    for (int i = 0; i < MAX_CHILD; i++)
    {
        childs[i] = fork();
        if (childs[i] == -1)
            return EXIT_FAILURE;
        else if (childs[i] == 0)
            task(i, data);
    }
    usleep(10000);

    // initalize array
    for (int i = 0; i < ARRAY_SIZE; i++)
        data[i] = i;

    // send sigusr1
    for (int i = 0; i < MAX_CHILD; i++)
        kill(childs[i], SIGUSR1);

    // waiting
    for (int i = 0; i < MAX_CHILD; i++)
        if ( wait(NULL) == -1 )
            perror("Wait error!\n");

    // print arrays
    for (int i = 0; i < ARRAY_SIZE; i++)
        printf("%d\t", data[i]);

    printf("\n");

    munmap(data, size);
    return EXIT_SUCCESS;
}
