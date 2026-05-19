#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
    int client_socket;
    char buffer[1024];

    struct sockaddr_in server_addr;

    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    if(client_socket < 0) {
        printf("Socket creation failed\n");
        return 1;
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to server
    connect(client_socket,
           (struct sockaddr*)&server_addr,
           sizeof(server_addr));

    // Input message
    printf("Enter message: ");
    fgets(buffer, sizeof(buffer), stdin);

    // Send message
    send(client_socket, buffer, sizeof(buffer), 0);

    // Receive reply
    recv(client_socket, buffer, sizeof(buffer), 0);

    printf("Server reply: %s\n", buffer);

    // Close socket
    close(client_socket);

    return 0;
}