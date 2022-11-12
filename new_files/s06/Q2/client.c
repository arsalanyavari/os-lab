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

int main(void)
{
    int n1, n2;
    long ans;
    char opr;
    int pipe;


    while(TRUE)
    {
        printf("Enter the operation\n\e[1;33m>> \e[0m");
        scanf("%c", &opr);
        if( (char)tolower(opr) != 'm' && (char)tolower(opr) != 'p' )
        {
            printf("\e[1;31mThe operation was wrong :\\ \e[0m");
            return 127;
        }
        printf("Enter the numbers\n\e[1;33m>> \e[0m");
        scanf("%d %d", &n1 ,&n2);
        getchar();
        pipe = open(FIFO_PATH, O_WRONLY);
        write(pipe, &opr, sizeof(opr));
        write(pipe, &n1, sizeof(n1));
        write(pipe, &n2, sizeof(n2));
        close(pipe);

        pipe = open(FIFO_PATH, O_RDONLY);
        read(pipe, &ans, sizeof(ans));
        printf("\e[1;35mThe resault: %ld\e[0m\n", ans);
        close(pipe);
    }
    return 0;
}
