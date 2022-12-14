#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int SIZE = 20;
int STRIDE = 10;
int *a;

void *compare_function(void *x)
{
    if (a[*(int *) x] > a[*(int *) x + STRIDE])
        a[*(int *) x] = a[*(int *) x + STRIDE];

    int *ret = malloc(sizeof(int));
    *ret = 0;
    pthread_exit((void *) ret);
}

int main(void)
{
    srand(time(NULL));
    a = malloc(sizeof(int) * SIZE);
    int *retval = malloc(sizeof(int));

    for (int i = 0; i < SIZE; i++)
    {
        a[i] = rand() % 100;
        printf("'%d'\t", a[i]);
    }

    printf("\n");

    while (STRIDE)
    {
        pthread_t threads[STRIDE];
        int *indexes = malloc(sizeof(int) * STRIDE);
        for (int i = 0; i < STRIDE; i++)
        {
            indexes[i] = i;
            pthread_create(&threads[i], NULL, compare_function, (void *) &indexes[i]);
            //sleep(1);
        }


        for (int i = 0; i < STRIDE; i++)
            pthread_join(threads[i], (void **) &retval);

        STRIDE /= 2;
    }
    printf("Result: %d\n", a[0]);
    return 0;
}
