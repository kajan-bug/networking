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
    socklen_t addr_size;

    // Create socket
    client_socket = socket(AF_INET, SOCK_DGRAM, 0);

    if(client_socket < 0) {
        printf("Socket creation failed\n");
        return 1;
    }

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9000);
    server_addr.sin_addr.s_addr =
            inet_addr("127.0.0.1");

    // Input message
    printf("Enter message: ");
    fgets(buffer, sizeof(buffer), stdin);

    addr_size = sizeof(server_addr);

    // Send message to server
    sendto(client_socket,
          buffer,
          strlen(buffer),
          0,
          (struct sockaddr*)&server_addr,
          addr_size);

    // Receive reply
    recvfrom(client_socket,
            buffer,
            sizeof(buffer),
            0,
            (struct sockaddr*)&server_addr,
            &addr_size);

    printf("Server reply: %s\n", buffer);

    // Close socket
    close(client_socket);

    return 0;
}