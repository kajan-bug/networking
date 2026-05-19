#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define WINDOW_SIZE 3

struct Frame {

    int type;   // 1 = DATA , 0 = ACK
    int seq;
    int ack;

    char data[100];
};

int main() {

    int server_socket;

    struct sockaddr_in server_addr,
                       client_addr;

    socklen_t addr_size;

    struct Frame recv_frame,
                 send_frame;

    int received[100] = {0};

    // Create socket
    server_socket = socket(AF_INET,
                           SOCK_DGRAM,
                           0);

    // Configure server
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9000);

    server_addr.sin_addr.s_addr =
            INADDR_ANY;

    // Bind
    bind(server_socket,
        (struct sockaddr*)&server_addr,
        sizeof(server_addr));

    printf("Selective Repeat Server Waiting...\n");

    addr_size = sizeof(client_addr);

    while(1){

        // Receive frame
        recvfrom(server_socket,
                &recv_frame,
                sizeof(recv_frame),
                0,
                (struct sockaddr*)&client_addr,
                &addr_size);

        // Check frame
        if(recv_frame.type == 1){

            printf("\nFrame received\n");

            printf("Sequence : %d\n",
                    recv_frame.seq);

            printf("Data     : %s\n",
                    recv_frame.data);

            // Mark frame received
            received[recv_frame.seq] = 1;

            // Send ACK
            send_frame.type = 0;

            send_frame.ack =
                    recv_frame.seq;

            sendto(server_socket,
                  &send_frame,
                  sizeof(send_frame),
                  0,
                  (struct sockaddr*)&client_addr,
                  addr_size);

            printf("ACK sent : %d\n",
                    send_frame.ack);
        }
    }

    close(server_socket);

    return 0;
}