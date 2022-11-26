#include "protocol.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int main(void)
{
    int fd = shm_open(NAME, O_RDONLY, 0666);
    if (fd<0)
    {
        perror("shm_open()");
        return EXIT_FAILURE;
    }

    struct Data *data = (struct Data *)mmap(0, 2 * sizeof(struct Data), PROT_READ, MAP_SHARED, fd, 0);
    if(data == (struct Data *)-1)
    {
        perror("mmap()");
        return EXIT_FAILURE;
    }

    printf("reciver address: %p\n", data);

    for(int j=0; j < 2; j++ )
    {

        printf("DATA %d\n", j+1);
        for (int i = 0; i < NUM; i++)
            printf("num%d: %d\n", i+1, data[j].array[i]);

        printf("msg 1: %s\n\n", data[j].str);
    }

    munmap(data, sizeof(struct Data));

    close(fd);

    // delete file
    shm_unlink(NAME);
    return EXIT_SUCCESS;
}
