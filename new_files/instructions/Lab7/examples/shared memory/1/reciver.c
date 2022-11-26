#include "protocol.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int main()
{
    int fd = shm_open(NAME, O_RDONLY, 0666);
    if (fd<0) {
        perror("shm_open()");
        return EXIT_FAILURE;
    }

    int size = ARRAY_S + STR_L;

    void *data = mmap(0, size, PROT_READ, MAP_SHARED, fd, 0);
    if(data == (void *)-1){
        perror("mmap()");
        return EXIT_FAILURE;
    }

    int *array = (int *)data;
    char *msg = (char *)(data + ARRAY_S);
    
    printf("reciver address: %p\n", data);

    for (int i = 0; i < NUM; i++) {
        printf("num%d: %d\n", i, array[i]);
    }

    printf("msg: %s\n", msg);

    munmap(data, size);

    close(fd);

    // delete file
    shm_unlink(NAME);
    return EXIT_SUCCESS;
}