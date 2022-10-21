#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
    char readBuffer[1024] = {0};
    int readFile=open("/dev/iut_device", O_RDWR);
    char buffer[100]={0};
    sprintf(buffer, "%s,%s,%s,%s", argv[1], argv[2], argv[3], argv[4]);
    printf("%s\n", buffer);
    write(readFile, buffer, 100);
    read(readFile,readBuffer, 1024);
    fprintf(stdout,"%s\n",readBuffer);
    close(readFile);

    return 0;
}
