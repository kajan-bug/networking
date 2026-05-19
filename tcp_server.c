#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    int server_socket, client_socket;
    char buffer[1024];

    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if(server_socket < 0) {
        printf("Socket creation failed\n");
        return 1;
    }

    // Configure server
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9000);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket
    bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // Listen for connections
    listen(server_socket, 5);

    printf("Server waiting for connection...\n");

    addr_size = sizeof(client_addr);

    // Accept client 
    client_socket = accept(server_socket,
                          (struct sockaddr*)&client_addr,
                          &addr_size);

    // Receive message
    recv(client_socket, buffer, sizeof(buffer), 0);

    printf("Message from client: %s\n", buffer);

    // Send response
    char reply[] = "Message received by server";
    send(client_socket, reply, sizeof(reply), 0);

    // Close sockets
    close(client_socket);
    close(server_socket);

    return 0;
}