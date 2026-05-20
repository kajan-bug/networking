#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {

    int server_socket,
        client_socket;

    char buffer[1024],
         file_data[1024];

    FILE *fp;

    struct sockaddr_in server_addr,
                       client_addr;

    socklen_t addr_size;

    // Create socket
    server_socket = socket(AF_INET,
                           SOCK_STREAM,
                           0);

    if(server_socket < 0){

        printf("Socket creation failed\n");

        return 1;
    }

    // Configure server
    server_addr.sin_family = AF_INET;

    server_addr.sin_port = htons(2121);

    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind
    bind(server_socket,
        (struct sockaddr*)&server_addr,
        sizeof(server_addr));

    // Listen
    listen(server_socket, 5);

    printf("Server Waiting...\n");

    addr_size = sizeof(client_addr);

    // Accept client
    client_socket = accept(server_socket,
                          (struct sockaddr*)&client_addr,
                          &addr_size);

    // Receive filename
    recv(client_socket,
         buffer,
         sizeof(buffer),
         0);

    printf("Requested File : %s\n", buffer);

    // Open file
    fp = fopen(buffer, "r");

    if(fp == NULL){

        strcpy(buffer, "error");

        send(client_socket,
             buffer,
             strlen(buffer),
             0);
    }

    else{

        while(fgets(file_data,
                    sizeof(file_data),
                    fp) != NULL){

            send(client_socket,
                 file_data,
                 strlen(file_data),
                 0);

            sleep(1);
        }

        strcpy(buffer, "completed");

        send(client_socket,
             buffer,
             strlen(buffer),
             0);

        fclose(fp);
    }

    close(client_socket);

    close(server_socket);

    return 0;
}