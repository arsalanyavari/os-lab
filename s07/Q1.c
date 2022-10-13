#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "sys/types.h"
#include "signal.h"

#define MAX_TRY 2
int cnt = 0;

void handler()
{
    if(++cnt == MAX_TRY)
        exit(0);
}

int main(void)
{
    struct sigaction action;
    action.sa_handler = handler;
    action.sa_flags = 0;
    sigaction(SIGINT,(struct sigaction *) &action, NULL);
    while(1);
    return 0;
}
