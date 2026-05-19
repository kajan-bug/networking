#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {

    int client_socket;

    char buffer[1024];

    struct sockaddr_in server_addr;

    // Create socket
    client_socket = socket(AF_INET,
                           SOCK_STREAM,
                           0);

    if(client_socket < 0){

        printf("Socket creation failed\n");

        return 1;
    }

    // Configure server address
    server_addr.sin_family = AF_INET;

    server_addr.sin_port = htons(2121);

    server_addr.sin_addr.s_addr =
            inet_addr("127.0.0.1");

    // Connect to FTP server
    connect(client_socket,
           (struct sockaddr*)&server_addr,
           sizeof(server_addr));

    // Receive welcome message
    recv(client_socket,
         buffer,
         sizeof(buffer),
         0);

    printf("%s\n", buffer);

    // USER command
    strcpy(buffer,
           "USER admin\r\n");

    send(client_socket,
         buffer,
         strlen(buffer),
         0);

    recv(client_socket,
         buffer,
         sizeof(buffer),
         0);

    printf("%s\n", buffer);

    // PASS command
    strcpy(buffer,
           "PASS 1234\r\n");

    send(client_socket,
         buffer,
         strlen(buffer),
         0);

    recv(client_socket,
         buffer,
         sizeof(buffer),
         0);

    printf("%s\n", buffer);

    // LIST command
    strcpy(buffer,
           "LIST\r\n");

    send(client_socket,
         buffer,
         strlen(buffer),
         0);

    recv(client_socket,
         buffer,
         sizeof(buffer),
         0);

    printf("%s\n", buffer);

    // QUIT command
    strcpy(buffer,
           "QUIT\r\n");

    send(client_socket,
         buffer,
         strlen(buffer),
         0);

    recv(client_socket,
         buffer,
         sizeof(buffer),
         0);

    printf("%s\n", buffer);

    // Close socket
    close(client_socket);

    return 0;
}