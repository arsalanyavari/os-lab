#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>

#define SERVER_PORT 6000
#define SERVER_IP "127.0.0.1"
#define COUNT 256
#define MAX_CLIENT 5
#define TRUE 1

char buffer [COUNT];
int cnt = -1;

void *runner(void *in)
{
    int client_socket = (int)in;
    cnt = (cnt == MAX_CLIENT-1) ? 0 : ++cnt;
    while (TRUE)
    {
        printf("\e[1;35mClient %d is connected\e[0m\n", cnt);
        bzero(buffer, COUNT);
        while (read(client_socket, buffer, COUNT))
        {
            printf("\e[1;33mThe client %d message is:\e[0m %s\n", cnt, buffer);
            write(client_socket, buffer, strlen(buffer));
            if (! strcmp(buffer, "bye"))
            {
                close(client_socket);
                break;
            }
            bzero(buffer, COUNT);
        }
        printf ("\e[1;31mclient %d connection is closed.\e[0m\n", cnt);
        return 0;
    }
}

int main(void)
{
    int pid[MAX_CLIENT];
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    server_address.sin_family = AF_INET; //IPv4
    server_address.sin_port = htons(SERVER_PORT);
    server_address.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_socket = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
    bind (server_socket, (struct sockaddr *) & server_address, sizeof(server_address));

    listen (server_socket, MAX_CLIENT);
    int clientsize = sizeof(client_address);
    while(TRUE)
    {
        if ((client_socket = accept(server_socket, (struct sockaddr *)&client_address, &(clientsize))) >= 0)
        {
            pthread_t thread;
            pthread_create(&thread, NULL, runner, (void *)client_socket);
        }
        else
            printf("Error in accepting the connection from the client\n ");
    }
    return 0;
}
