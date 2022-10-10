#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#define SIZE 10
int A[SIZE];
int stride;

void *runner(void *args)
{
    int x = (int)args;
    int min = A[x];
    for (int i = x; i <= x + stride; i++)
        if (A[i] < min)
            min = A[i];
    A[x] = min;
}

int main(void)
{
    printf("Enter the array numbers...\n\e[1;33m>> \e[0m");
    for (int i = 0; i < SIZE; i++)
        scanf("%d", &A[i]);

    stride = ceil(SIZE / 2.0);
    while (stride)
    {
        pthread_t threads[stride];
        for (int i = 0; i < stride; i++)
        {
            pthread_create(threads + i, NULL, runner, (void *)i);
            pthread_join(threads[i], 0);
        }
        stride = (stride == 1) ? 0 : ceil(stride / 2.0);
    }
    printf("\e[1;32mThe minimum number is: %d\e[0m\n", A[0]);
}
