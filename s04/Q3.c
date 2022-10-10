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

int main()
{
    char *command = NULL;
    char buffer[COUNT];
    size_t size;
    time_t t;
    struct tm *tm;
    struct timeval start, stop;
    int file;

    if (access("./log.txt", F_OK) != -1)
        file = open("./log.txt", O_WRONLY | O_APPEND, 00777);
    else
    {
        file = open("./log.txt", O_CREAT | O_WRONLY , 00777);
        sprintf(buffer, "%s", "Date\tTime\tExe_Time(ms)\tcommand(path)\n-------------------------------------------------\n");
        write(file, buffer, strlen(buffer));
    }
    while (printf("\e[1;33m>> \e[0m") && getline(&command, &size, stdin))
    {
        gettimeofday(&start, NULL);
        system(command);
        gettimeofday(&stop, NULL);

        char str_time[COUNT];
        char str_date[COUNT];

        t = time(NULL);
        tm = localtime(&t);

        strftime(str_time, sizeof(str_time), "%H:%M", tm);
        strftime(str_date, sizeof(str_date), "%Y/%m", tm);

        long elapsed = (stop.tv_sec - start.tv_sec) * 1000 + (stop.tv_usec - start.tv_usec) / 1000;
        sprintf(buffer, "%s\t%s\t\t%ld\t\t\t\t%s\n-------------------------------------------------\n", str_date, str_time, elapsed, command);
        write(file, buffer, strlen(buffer));
    }
    close(file);
    return 0;
}
