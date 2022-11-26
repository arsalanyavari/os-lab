#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include "protocol.h"


int main()
{
    int fd = shm_open(NAME, O_CREAT | O_EXCL | O_RDWR, 0600);
    if (fd<0) {
        perror("shm_open()");
        return EXIT_FAILURE;
    }
    
    int size = ARRAY_S + STR_L;

    ftruncate(fd, size);

    void *data = mmap(0, size, PROT_READ | PROT_WRITE,
     MAP_SHARED, fd, 0);
    if(data == (void *)-1){
        perror("mmap()");
        return EXIT_FAILURE;
    }

    int *array = (int *)data;
    char *msg = (char *)(data + ARRAY_S); // get address of messge
    
    printf("sender address: %p\n", data);

    // write array in shared memory
    for (int i = 0; i < NUM; i++) {
        array[i] = i*i;
    }

    // write messge in shared memory
    strncat(msg, "Hi Shared Memory!", STR_L);

    munmap(data, size);

    close(fd);
    return EXIT_SUCCESS;
}