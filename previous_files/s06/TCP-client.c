#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <libgen.h>

#define SERVER_PORT 6000
#define COUNT 256
#define SERVER_IP "127.0.0.1"

char *get_filename_ext(char *filename) {
    char *dot = strrchr(filename, '.');
    if(!dot || dot == filename)
        return "";
    return dot;
}

int main(void)
{
    int client_socket;
    char buffer[COUNT], filename[COUNT];
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = inet_addr(SERVER_IP);

    client_socket = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (connect (client_socket, (struct sockaddr *) &server, sizeof(server)) == 0)
    {
        printf("Client is connected to the server!\n");
        printf("\e[1;33m>> \e[0m");
        bzero (buffer ,COUNT);
        fgets(buffer, COUNT, stdin);

        if (buffer[strlen(buffer) - 1] == '\n')
            buffer[strlen(buffer) - 1] = '\0';

        write(client_socket, buffer, COUNT);
        printf("You're request has been sent to server.\nWaiting for response...\n");

        if (! strlen(get_filename_ext(basename(strdup(buffer)))))
            strcat(buffer, "_cpy");

        for (int i = strlen(get_filename_ext(basename(strdup(buffer)))), j = strlen(buffer) - 1; i > 0 ; i--, j--)
        {
            buffer[j+4] = buffer[j];
            switch(i) {
                case 1:
                    buffer[j]='_';
                    break;
                case 2:
                    buffer[j]='c';
                    break;
                case 3:
                    buffer[j]='p';
                    break;
                case 4:
                    buffer[j]='y';
                    break;
            }
        }
        sprintf(filename, "%s", buffer);
        read(client_socket, buffer, COUNT);
        int filesize = 0;
        sscanf(buffer, "%d", &filesize);
        if (filesize)
        {
            FILE *file = fopen(filename, "w");
            printf("Downloading..");
            while (ftell(file) < filesize)
            {
                printf(".");
                bzero(buffer, COUNT);
                read(client_socket, buffer, COUNT);
                fwrite(buffer, sizeof(char), strlen(buffer), file);
            }
            printf("\nDone.\n");
        }
    }
    else
        printf("Error in connecting to the server\n");

    return 0;
}
