#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO_PATH ".Q2.pipe"
#define COUNT 256
#define TRUE 1

struct Data
{
    char opr;
    int n1, n2;
}data;

int main(void)
{
    long ans;
    int pipe;

    while(TRUE)
    {
        printf("Enter the operation\n\e[1;33m>> \e[0m");
        scanf("%c", &data.opr);
        if( (char)tolower(data.opr) != 'm' && (char)tolower(data.opr) != 'p' )
        {
            printf("\e[1;31mThe operation was wrong :\\ \e[0m");
            return 127;
        }
        printf("Enter the numbers\n\e[1;33m>> \e[0m");
        scanf("%d %d", &data.n1 ,&data.n2);
        getchar();
        pipe = open(FIFO_PATH, O_WRONLY);
        write(pipe, &data.opr, sizeof(data.opr));
        write(pipe, &data.n1, sizeof(data.n1));
        write(pipe, &data.n2, sizeof(data.n2));
        close(pipe);

        pipe = open(FIFO_PATH, O_RDONLY);
        read(pipe, &ans, sizeof(ans));
        printf("\e[1;35mThe resault: %ld\e[0m\n", ans);
        close(pipe);
    }
    return 0;
}
