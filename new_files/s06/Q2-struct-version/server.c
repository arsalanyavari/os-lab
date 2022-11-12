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

struct Data
{
    char cmd;
    int n1, n2;
}data;

int main(void)
{
    printf("\e[1;32m Server is up...\e[0m\n");
    long ans;
    int pipe;

    mkfifo(FIFO_PATH,0777);

    while(TRUE)
    {
        pipe = open(FIFO_PATH, O_RDONLY);
        read(pipe, &data.cmd, sizeof(data.cmd));
        read(pipe, &data.n1, sizeof(data.n1));
        read(pipe, &data.n2, sizeof(data.n2));
        close(pipe);

        if( (char)tolower(data.cmd) == 'm' )
            ans = data.n1 * data.n2;
        else if ( (char) tolower(data.cmd) == 'p' )
            ans = pow(data.n1, data.n2);
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

