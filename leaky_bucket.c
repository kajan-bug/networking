#include <stdio.h>
#include <stdlib.h>

int main() {

    int bucket_size, output_rate;

    int packets[20];

    int n, i;

    int bucket = 0;

    // Input bucket capacity
    printf("Enter bucket size : ");

    scanf("%d", &bucket_size);

    // Input output rate
    printf("Enter output rate : ");

    scanf("%d", &output_rate);

    // Number of packets
    printf("Enter number of packets : ");

    scanf("%d", &n);

    // Input packet sizes
    for(i = 0; i < n; i++) {

        printf("Enter packet %d size : ",
                i + 1);

        scanf("%d", &packets[i]);
    }

    printf("\n");

    // Process packets
    for(i = 0; i < n; i++) {

        printf("Incoming packet size : %d\n",
                packets[i]);

        // Check overflow
        if(bucket + packets[i] > bucket_size) {

            printf("Bucket overflow\n");

            printf("Packet dropped\n");
        }
        else {

            // Add packet to bucket
            bucket = bucket + packets[i];

            printf("Bucket content : %d\n",
                    bucket);
        }

        // Leak packets
        printf("Leaked : %d\n",
                output_rate);

        bucket = bucket - output_rate;

        // Avoid negative value
        if(bucket < 0) {

            bucket = 0;
        }

        printf("Remaining in bucket : %d\n\n",
                bucket);
    }

    return 0;
}