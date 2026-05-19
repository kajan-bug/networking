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

    int client_socket;

    struct sockaddr_in server_addr;

    socklen_t addr_size;

    struct Frame send_frame,
                 recv_frame;

    int base = 0;

    int next_seq = 0;

    // Create socket
    client_socket = socket(AF_INET,
                           SOCK_DGRAM,
                           0);

    // Configure server
    server_addr.sin_family = AF_INET;

    server_addr.sin_port = htons(9000);

    server_addr.sin_addr.s_addr =
            inet_addr("127.0.0.1");

    while(1){

        // Send window frames
        while(next_seq < base + WINDOW_SIZE){

            send_frame.type = 1;

            send_frame.seq = next_seq;

            printf("\nEnter data for frame %d : ",
                    next_seq);

            scanf("%s",
                  send_frame.data);

            sendto(client_socket,
                  &send_frame,
                  sizeof(send_frame),
                  0,
                  (struct sockaddr*)&server_addr,
                  sizeof(server_addr));

            printf("Frame sent : %d\n",
                    next_seq);

            next_seq++;
        }

        // Receive ACK
        addr_size = sizeof(server_addr);

        recvfrom(client_socket,
                &recv_frame,
                sizeof(recv_frame),
                0,
                (struct sockaddr*)&server_addr,
                &addr_size);

        // Correct ACK
        if(recv_frame.type == 0){

            printf("ACK received : %d\n",
                    recv_frame.ack);

            // Slide window
            base = recv_frame.ack + 1;

        }else{

            printf("ACK not received\n");

            printf("Go Back and resend\n");

            next_seq = base;
        }
    }

    close(client_socket);

    return 0;
}