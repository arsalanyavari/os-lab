#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

#define TRUE 1

sem_t chopstick[5];

int cat_eat(int num)
{
    int value = 0, value2 = 0;
    sem_getvalue(&chopstick[num], &value);
    sem_getvalue(&chopstick[(num + 1) % 5], &value2);
    return value + value2 == 2;
}

void think(int phil)
{
    printf("Philosopher %d is thinking\n", phil);
    sleep(rand() % 3);
}


void eat(int phil)
{
    printf("Philosopher %d is hungry\n", phil);
    sem_wait(&chopstick[phil]);
    sleep(1);
    sem_wait(&chopstick[(phil + 1) % 5]);
    sleep(rand() % 3);
    printf("Philosopher %d is eating\n", phil);
    sem_post(&chopstick[(phil + 1) % 5]);
    sem_post(&chopstick[phil]);
    printf("Philosopher %d has finished eating\n", phil);
}


void *philosopher(void *num)
{
    int phil = *(int *) num;
    while (TRUE)
    {
        think(phil);
        while (!cat_eat(phil));
        eat(phil);
    }
}


int main(void)
{
    int i, a[5];
    pthread_t tid[5];

    for (i = 0; i < 5; i++)
        sem_init(&chopstick[i], 0, 1);

    for (i = 0; i < 5; i++)
    {
        a[i] = i;
        pthread_create(&tid[i], NULL, philosopher, (void *) &a[i]);
    }

    for (i = 0; i < 5; i++)
        pthread_join(tid[i], NULL);

    return 0;
}
