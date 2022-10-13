#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <libgen.h>

#define SERVER_PORT 6000
#define COUNT 256
#define SERVER_IP "127.0.0.1"
#define TRUE 1

int main()
{
    int client_socket;
    char buffer [COUNT];
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    client_socket = socket ( AF_INET, SOCK_STREAM, IPPROTO_TCP );

    if (connect ( client_socket , (struct sockaddr * ) &server , sizeof(server))==0)
        printf("\e[1;32mClient is connected to the server :)\e[0m\n");
    else
    {
        printf("\e[1;31mError in connecting to the server\e[0m\n");
        return 0;
    }
        while(TRUE)
    {
        printf("\e[1;33m>> \e[0m");
        bzero (buffer ,COUNT);
        scanf("%s", buffer);
        write(client_socket , buffer , COUNT);
        printf("msg is sent to the server!\n");
        read(client_socket, buffer, COUNT);
        printf("\e[1;33mThe server message is:\e[0m %s\n", buffer);
        if(! strcmp(buffer, "bye"))
            break;
    }
    return 0;
}
