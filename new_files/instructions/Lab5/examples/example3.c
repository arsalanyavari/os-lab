#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>

int main(int argc, char *argv[])
{
	struct timeval start, stop;
	int r;

	srand(time(NULL));
	r = rand()%6 + 1;

	gettimeofday(&start, NULL);

	sleep(r);

	gettimeofday(&stop, NULL);

	long sec = stop.tv_sec - start.tv_sec;
	float us = stop.tv_usec - start.tv_usec;

	long elapsed = sec * 1000 + us/1000.0;
	printf("sleep(%d) run in %ld msec\n", r, elapsed);

	return 0;
}
