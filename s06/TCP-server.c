#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERVER_PORT 6000
#define SERVER_IP "127.0.0.1"
#define COUNT 256
#define MAX_CLIENT 5
#define TRUE 1

int main(void)
{
    char buffer [COUNT];
    int pid[MAX_CLIENT];
    int server_socket, client_socket, cnt = 0;
    struct sockaddr_in server_address, client_address;
    server_address.sin_family = AF_INET; //IPv4
    server_address.sin_port = htons(SERVER_PORT);
    server_address.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_socket = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
    bind (server_socket, (struct sockaddr *) & server_address, sizeof(server_address));

    while(TRUE)
    {
        listen (server_socket, 1);
        if (cnt < MAX_CLIENT)
        {
            pid[cnt] = fork();

            if (! pid[cnt])
            {
                int clientsize = sizeof(client_address);
                if ((client_socket = accept ( server_socket , (struct sockaddr * ) & client_address , &(clientsize)))>=0)
                {
                    printf("\e[1;35mA connection from client %d is recieved\e[0m\n", cnt);
                    bzero(buffer, COUNT);
                    if (! read(client_socket , buffer , COUNT))
                        printf ("\e[1;31mclient %d connection is closed.\e[0m\n", cnt);
                    else
                    {
                        printf ("\e[1;32mclient %d try to download %s from server...\e[0m\n", cnt, buffer);

                        FILE *file = fopen(buffer, "r");
                        if (! file)
                        {
                            printf("\e[1;31mFile not found. rejecting the client...\e[0m\n");
                            sprintf(buffer, "%d", 0);
                            write(client_socket, buffer, COUNT);
                        }
                        else
                        {
                            fseek(file, 0L, SEEK_END);
                            int filesize = ftell(file);
                            fseek(file, 0L, SEEK_SET);
                            printf("Filesize is %d Bytes. Preparing to upload...\n", filesize);
                            sprintf(buffer, "%d", filesize);
                            write(client_socket, buffer, COUNT);

                            printf("Uploading...");
                            while (fread(buffer, sizeof(char), sizeof(buffer), file) > 0)
                            {
                                printf(".");
                                write(client_socket, buffer, strlen(buffer));
                                bzero(buffer, COUNT);
                            }
                            printf("\nDone.\n");
                        }
                    }
                }
            }
            else
                cnt++;
        }
    }
    return 0;
}
