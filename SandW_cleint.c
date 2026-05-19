#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

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

    int seq = 0;

    // Create UDP socket
    client_socket = socket(AF_INET,
                           SOCK_DGRAM,
                           0);

    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9000);

    server_addr.sin_addr.s_addr =
            inet_addr("127.0.0.1");

    while(1){

        // Create DATA frame
        send_frame.type = 1;

        send_frame.seq = seq;

        send_frame.ack = 0;

        printf("\nEnter data : ");

        scanf("%s", send_frame.data);

        // Send frame
        sendto(client_socket,
              &send_frame,
              sizeof(send_frame),
              0,
              (struct sockaddr*)&server_addr,
              sizeof(server_addr));

        printf("Frame sent : %d\n",
                seq);

        addr_size = sizeof(server_addr);

        // Wait for ACK
        recvfrom(client_socket,
                &recv_frame,
                sizeof(recv_frame),
                0,
                (struct sockaddr*)&server_addr,
                &addr_size);

        // Validate ACK
        if(recv_frame.type == 0 &&
           recv_frame.ack == seq + 1){

            printf("ACK received : %d\n",
                    recv_frame.ack);

            seq++;

        }else{

            printf("ACK not received\n");

            printf("Resending frame...\n");
        }
    }

    close(client_socket);

    return 0;
}