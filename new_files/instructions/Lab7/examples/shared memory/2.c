#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

#define MSG_SIZE 30

void task(char *shm)
{
    strncat(shm, "Hello! I'm so Happy in IUT;)", MSG_SIZE);
    printf("child(pid:%d) has writen message in anonymous shared Memory.\n", getpid());
    printf("The address of memory in child is: %p\n", shm);
    exit(EXIT_SUCCESS);
}

int main()
{
    char *msg = "Hello! I'm so Happy in IUT;)";

    char *data = (char *)mmap(0, MSG_SIZE, PROT_READ | PROT_WRITE,
     MAP_SHARED | MAP_ANONYMOUS, 0, 0);
    if(data == (void *)-1){
        perror("mmap()");
        return EXIT_FAILURE;
    }

    pid_t cpid = fork();
    if( cpid == -1 ) {
        perror("fork()");
        return EXIT_FAILURE;
    } else if (cpid == 0) { // in child
        task(data);
    }

    // in parent
    sleep(1); // waiting for child to write msg in memory
    printf("parent(pid:%d) read message from memory, msg: %s\n", getpid(), data);
    printf("The address of memory in parent is: %p\n", data);

    munmap(data, MSG_SIZE);
    return EXIT_SUCCESS;
}