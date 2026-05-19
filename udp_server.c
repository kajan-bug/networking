#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {

    int server_socket;
    char buffer[1024];

    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;

    // Create socket
    server_socket = socket(AF_INET, SOCK_DGRAM, 0);

    if(server_socket < 0) {
        printf("Socket creation failed\n");
        return 1;
    }

    // Configure server
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9000);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket
    bind(server_socket,
        (struct sockaddr*)&server_addr,
        sizeof(server_addr));

    printf("UDP Server waiting...\n");

    addr_size = sizeof(client_addr);

    // Receive message from client
    recvfrom(server_socket,
            buffer,
            sizeof(buffer),
            0,
            (struct sockaddr*)&client_addr,
            &addr_size);

    printf("Message from client: %s\n", buffer);

    // Send reply
    char reply[] = "Message received by UDP server";

    sendto(server_socket,
          reply,
          sizeof(reply),
          0,
          (struct sockaddr*)&client_addr,
          addr_size);

    // Close socket
    close(server_socket);

    return 0;
}