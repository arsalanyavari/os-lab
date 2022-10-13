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

int main(void)
{
    int client_socket, server_address_len;
    char buffer[COUNT];
    struct sockaddr_in server_address, client_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);
    server_address.sin_addr.s_addr=inet_addr(SERVER_IP);
    client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    printf("\e[1;33m>> \e[0m");
    fgets(buffer, COUNT, stdin);
    sendto(client_socket, (const char *)buffer, strlen(buffer), MSG_CONFIRM,(const struct sockaddr *) &server_address, sizeof(server_address));
    strcpy(buffer, "          "); //flush the buffer
    recvfrom(client_socket, (char *)buffer, COUNT, MSG_WAITALL, (struct sockaddr*) &server_address, &server_address_len);
    printf("The resault: %s\n", buffer);
    close(client_socket);
    return 0;
}
