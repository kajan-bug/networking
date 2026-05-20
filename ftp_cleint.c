#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {

    int client_socket;

    char buffer[1024],
         filename[100],
         newfile[100];

    FILE *fp;

    struct sockaddr_in server_addr;

    // Create socket
    client_socket = socket(AF_INET,
                           SOCK_STREAM,
                           0);

    if(client_socket < 0){

        printf("Socket creation failed\n");

        return 1;
    }

    // Configure server
    server_addr.sin_family = AF_INET;

    server_addr.sin_port = htons(2121);

    server_addr.sin_addr.s_addr =
            inet_addr("127.0.0.1");

    // Connect
    connect(client_socket,
           (struct sockaddr*)&server_addr,
           sizeof(server_addr));

    printf("Connected to Server\n");

    // Input filename
    printf("Enter existing file name : ");

    scanf("%s", filename);

    printf("Enter new file name : ");

    scanf("%s", newfile);

    // Create new file
    fp = fopen(newfile, "w");

    // Send filename
    send(client_socket,
         filename,
         strlen(filename),
         0);

    while(1){

        memset(buffer, 0, sizeof(buffer));

        recv(client_socket,
             buffer,
             sizeof(buffer),
             0);

        // File not found
        if(strcmp(buffer, "error") == 0){

            printf("File not found\n");

            break;
        }

        // Transfer complete
        if(strcmp(buffer, "completed") == 0){

            printf("File transferred successfully\n");

            break;
        }

        // Display contents
        printf("%s", buffer);

        fprintf(fp, "%s", buffer);
    }

    fclose(fp);

    close(client_socket);

    return 0;
}