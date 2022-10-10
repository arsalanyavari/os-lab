#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>

#define COUNT 255

int main(int argc, char *argv[])
{
    //1
    if (strcmp(argv[1], "-c") == 0)
        open(argv[3], O_CREAT, strtol(argv[2], NULL, 8));

    //2
    if (strcmp(argv[1], "-w") == 0)
    {
        char str[COUNT];
        fgets(str, COUNT, stdin);
        int openFile = open(argv[2], O_CREAT | O_WRONLY, 00755);
        write(openFile, str, strlen(str));
    }

    //3
    if (strcmp(argv[1], "-r") == 0)
    {
        char *buf;
        int openFile = open(argv[2], O_RDONLY);
        ssize_t f = read(openFile, buf, COUNT);
        printf("%s", buf);
    }

    //4
    if (strcmp(argv[1], "-m") == 0)
    {
        mkdir(argv[2], 00777);

        for(int i = atoi(argv[5]); i <= atoi(argv[6]); i++)
        {
            char cmd[COUNT];
            sprintf(cmd, "touch %s/%s_%d.%s", argv[1], argv[2], i, argv[3]);
            system(cmd);
        }
    }

    return 0;
}
