#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <fcntl.h>
#include <time.h>

#define COUNT 256
#define TRUE 1

int main()
{
    size_t size;
    time_t t;
    struct tm *tm;
    struct timeval start, stop;
    int status;
    char *args;
    pid_t pid;

    printf("Date\t\tTime\tExecution Time(ms)\tr\n-------------------------------------------------\n");

    while(TRUE)
    {
        srand(time(NULL));
        int r = rand() % 5 + 1;
        sprintf(args, "%d", r);
        pid_t pid = fork();
        gettimeofday(&start, NULL);
        if(! pid)
        {
            execl("app", "app", (const char *)args, NULL);
            exit(0);
        }
        wait(&status);

        gettimeofday(&stop, NULL);

        char str_time[COUNT];
        char str_date[COUNT];

        t = time(NULL);
        tm = localtime(&t);

        strftime(str_time, sizeof(str_time), "%H:%M", tm);
        strftime(str_date, sizeof(str_date), "%Y-%m-%d", tm);

        long elapsed = (stop.tv_sec - start.tv_sec) * 1000 + (stop.tv_usec - start.tv_usec) / 1000;
        printf("%s\t%s\t\t%ld\t\t%d\n-------------------------------------------------\n", str_date, str_time, elapsed, r);
    }
    return 0;
}
