#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {

    int server_socket,
        client_socket;

    char buffer[1024];

    struct sockaddr_in server_addr,
                       client_addr;

    socklen_t addr_size;

    // Create socket
    server_socket = socket(AF_INET,
                           SOCK_STREAM,
                           0);

    // Configure server
    server_addr.sin_family = AF_INET;

    server_addr.sin_port = htons(2525);

    server_addr.sin_addr.s_addr =
            INADDR_ANY;

    // Bind
    bind(server_socket,
        (struct sockaddr*)&server_addr,
        sizeof(server_addr));

    // Listen
    listen(server_socket, 5);

    printf("SMTP Server Waiting...\n");

    addr_size = sizeof(client_addr);

    // Accept client
    client_socket = accept(server_socket,
                          (struct sockaddr*)&client_addr,
                          &addr_size);

    // Welcome message
    strcpy(buffer,
           "220 SMTP Server Ready\r\n");

    send(client_socket,
         buffer,
         strlen(buffer),
         0);

    while(1){

        memset(buffer, 0, sizeof(buffer));

        recv(client_socket,
             buffer,
             sizeof(buffer),
             0);

        printf("Client : %s", buffer);

        // HELO
        if(strncmp(buffer,
                  "HELO",
                  4) == 0){

            strcpy(buffer,
                   "250 Hello\r\n");
        }

        // MAIL FROM
        else if(strncmp(buffer,
                       "MAIL FROM",
                       10) == 0){

            strcpy(buffer,
                   "250 Sender OK\r\n");
        }

        // RCPT TO
        else if(strncmp(buffer,
                       "RCPT TO",
                       7) == 0){

            strcpy(buffer,
                   "250 Receiver OK\r\n");
        }

        // DATA
        else if(strncmp(buffer,
                       "DATA",
                       4) == 0){

            strcpy(buffer,
                   "354 Enter Mail End with .\r\n");
        }

        // QUIT
        else if(strncmp(buffer,
                       "QUIT",
                       4) == 0){

            strcpy(buffer,
                   "221 Connection Closed\r\n");

            send(client_socket,
                 buffer,
                 strlen(buffer),
                 0);

            break;
        }

        // Mail body
        else{

            strcpy(buffer,
                   "250 Mail Sent Successfully\r\n");
        }

        send(client_socket,
             buffer,
             strlen(buffer),
             0);
    }

    close(client_socket);

    close(server_socket);

    return 0;
}