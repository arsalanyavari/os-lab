#ifndef PROTOCOL_H
#define PROTOCOL_H

#define NAME "/shmem-oslab"

#define NUM 5

#define ARRAY_S (NUM * sizeof(int))

#define STR_L 20

struct Data
{
    int array[NUM];
    char str[STR_L];
};


#endif
