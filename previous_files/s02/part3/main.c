#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COUNT 255

int main(void)
{
    int v1, v2;
    char prefix[COUNT], file_address[COUNT];
    
    //1
    scanf("%d", &v1);
    scanf("%d", &v2);

    //2
    scanf("%s", prefix);

    //3
    scanf("%s", file_address);
    
    //4 & 5
    for (int i = v1; i <= v2; i++)
    {
        char cmd[COUNT];

        sprintf(cmd, "adduser --disabled-password --gecos \"\" %s-%d", prefix, i);
        system(cmd);

        strcpy(cmd, "");

        sprintf(cmd, "cp %s /home/%s-%d", file_address, prefix, i);
        system(cmd);
    }

    return 0;
}
