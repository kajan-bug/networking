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

    if(client_socket < 0) {

        printf("Socket creation failed\n");

        return 1;
    }

    // Configure server address
    server_addr.sin_family = AF_INET;

    server_addr.sin_port = htons(2525);

    server_addr.sin_addr.s_addr =
            inet_addr("127.0.0.1");

    // Connect to SMTP server
    connect(client_socket,
           (struct sockaddr*)&server_addr,
           sizeof(server_addr));

    // Receive welcome message
    recv(client_socket,
         buffer,
         sizeof(buffer),
         0);

    printf("%s\n", buffer);

    // HELO command
    strcpy(buffer,
           "HELO localhost\r\n");

    send(client_socket,
         buffer,
         strlen(buffer),
         0);

    recv(client_socket,
         buffer,
         sizeof(buffer),
         0);

    printf("%s\n", buffer);

    // MAIL FROM
    strcpy(buffer,
           "MAIL FROM:<sender@gmail.com>\r\n");

    send(client_socket,
         buffer,
         strlen(buffer),
         0);

    recv(client_socket,
         buffer,
         sizeof(buffer),
         0);

    printf("%s\n", buffer);

    // RCPT TO
    strcpy(buffer,
           "RCPT TO:<receiver@gmail.com>\r\n");

    send(client_socket,
         buffer,
         strlen(buffer),
         0);

    recv(client_socket,
         buffer,
         sizeof(buffer),
         0);

    printf("%s\n", buffer);

    // DATA command
    strcpy(buffer,
           "DATA\r\n");

    send(client_socket,
         buffer,
         strlen(buffer),
         0);

    recv(client_socket,
         buffer,
         sizeof(buffer),
         0);

    printf("%s\n", buffer);

    // Send mail body
    strcpy(buffer,
           "Hello this is SMTP mail\r\n.\r\n");

    send(client_socket,
         buffer,
         strlen(buffer),
         0);

    recv(client_socket,
         buffer,
         sizeof(buffer),
         0);

    printf("%s\n", buffer);

    // QUIT
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