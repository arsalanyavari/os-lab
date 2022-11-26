#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "protocol.h"

int main(void)
{
    int fd = shm_open(NAME, O_CREAT | O_EXCL | O_RDWR, 0600);
    if (fd<0)
    {
        perror("shm_open()");
        return EXIT_FAILURE;
    }

    int size = 2 * sizeof(struct Data);

    ftruncate(fd, size);

    struct Data *data = (struct Data *)mmap(0, size, PROT_READ | PROT_WRITE,
     MAP_SHARED, fd, 0);
    if(data == (struct Data *)-1)
    {
        perror("mmap()");
        return EXIT_FAILURE;
    }

    srand(time(NULL));
    // write array in shared memory
    for (int i = 0; i < NUM; i++)
    {
        data[0].array[i] = rand()%5 + 1;
        data[1].array[i] = rand()%5 + 1;
    }

    // write messge in shared memory
    strncpy(data[0].str, "My Name: ", STR_L);
    strncpy(data[1].str, "Friend's Name: ", STR_L);

    munmap(data, size);

    close(fd);
    return EXIT_SUCCESS;
}
