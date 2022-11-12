#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>

#define FIFO_PATH ".Q2.pipe"
#define COUNT 256
#define TRUE 1

int main(void)
{
    printf("\e[1;32m Server is up...\e[0m\n");
    int n1, n2;
    long ans;
    char cmd;
    int pipe;

    mkfifo(FIFO_PATH,0777);

    while(TRUE)
    {
        pipe = open(FIFO_PATH, O_RDONLY);
        read(pipe, &cmd, sizeof(cmd));
        read(pipe, &n1, sizeof(n1));
        read(pipe, &n2, sizeof(n2));
        close(pipe);

        if( (char)tolower(cmd) == 'm' )
            ans = n1 * n2;
        else if ( (char) tolower(cmd) == 'p' )
            ans = pow(n1, n2);
        else
        {
            printf("\e[1;31m Server is down...\e[0m\n");
            return 127;
        }

        pipe = open(FIFO_PATH, O_WRONLY);
        write(pipe, &ans, sizeof(ans));
        close(pipe);
    }
    return 0;
}

