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

    server_addr.sin_port = htons(2121);

    server_addr.sin_addr.s_addr =
            INADDR_ANY;

    // Bind socket
    bind(server_socket,
        (struct sockaddr*)&server_addr,
        sizeof(server_addr));

    // Listen
    listen(server_socket, 5);

    printf("FTP Server Waiting...\n");

    addr_size = sizeof(client_addr);

    // Accept client
    client_socket = accept(server_socket,
                          (struct sockaddr*)&client_addr,
                          &addr_size);

    // Welcome message
    strcpy(buffer,
           "220 FTP Server Ready\r\n");

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

        // USER command
        if(strncmp(buffer,
                  "USER",
                  4) == 0){

            strcpy(buffer,
                   "331 Username OK Need Password\r\n");
        }

        // PASS command
        else if(strncmp(buffer,
                       "PASS",
                       4) == 0){

            strcpy(buffer,
                   "230 Login Successful\r\n");
        }

        // LIST command
        else if(strncmp(buffer,
                       "LIST",
                       4) == 0){

            strcpy(buffer,
                   "150 File List\nfile1.txt\nfile2.txt\n");
        }

        // QUIT command
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

        else{

            strcpy(buffer,
                   "500 Invalid Command\r\n");
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