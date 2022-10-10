#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000
#define COUNT 256
#define TRUE 1

int main(void)
{
    int server_socket;
    char buffer[COUNT];
    struct sockaddr_in server_address, client_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_address.sin_port = htons(SERVER_PORT);
    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    bind(server_socket, (const struct sockaddr *)&server_address, sizeof(server_address));

    while(TRUE)
    {
        int client_address_len = sizeof(client_address);
        recvfrom(server_socket, (char *)buffer, COUNT, MSG_WAITALL, ( struct sockaddr*) &client_address, &client_address_len);
        int a, b;
        sscanf(buffer, "%d %d", &a, &b);
        printf("%d + %d = \e[1;32m%d\e[0m\n", a, b, a+b);
        sprintf(buffer, "%d", a+b);
        sendto(server_socket, (const char *)buffer, strlen(buffer), MSG_CONFIRM, (const struct sockaddr *) &client_address, client_address_len);
    }
    return 0;
}
