#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


int main(int argc, char const *argv[])
{
    int fd = open("f.txt", O_RDWR);
    char *p = mmap(NULL, 6, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    pid_t cpid = fork();
    if (cpid < 0 ) {
         perror("fork()");
         return EXIT_FAILURE;
    } else if (cpid == 0) { // in child
         printf("c: mesg: %s\n", p);
         p[0] = 's';
         exit(EXIT_SUCCESS);
    }

    usleep(500*1000); // 500ms

    printf("p: mesg: %s\n", p);

    munmap(p, 6);

    return EXIT_SUCCESS;
}
