#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

int SIZE = 20;
int THREADS = 2;
int *a, *b;
int product = 0;
sem_t sem;

void *multiply_function(void *x)
{
    int index = *(int *)x;
    int local_product = 0;

    while (index< SIZE)
    {
        local_product += a[index] * b [index];
        index+=THREADS;
    }
    sem_wait(&sem);
    product+=local_product;
    sem_post(&sem);
    pthread_exit((void *) 0);
}

int main(void)
{
    sem_init(&sem, 0 , 1);
    srand(time(NULL));
    a = malloc(sizeof(int) * SIZE);
    b = malloc(sizeof(int) * SIZE);
    int *retval = malloc(sizeof(int));

    printf("A array: \n");
    for (int i = 0; i < SIZE; i++)
    {
        a[i] = rand() % 2;
        printf("'%d'\t", a[i]);
    }

    printf("\nB array: \n");

    for (int i = 0; i < SIZE; i++)
    {
        b[i] = rand() % 2;
        printf("'%d'\t", b[i]);
    }

    printf("\n");

    pthread_t threads[THREADS];
    int *indexes = malloc(sizeof(int) * SIZE);
    for (int i = 0; i < THREADS; i++)
    {
        indexes[i] = i;
        pthread_create(&threads[i], NULL, multiply_function, (void *) &indexes[i]);
        //sleep(1);
    }

    for (int i = 0; i < THREADS; i++)
        pthread_join(threads[i], NULL);

    printf("Product: %d\n", product);
    return 0;
}
