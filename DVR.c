#include <stdio.h>

struct router{

    unsigned cost[20];
    unsigned from[20];

}routingTable[10];

int main(){

    int costmat[20][20];

    int routers;
    int i, j, k;

    printf("Enter number of routers : ");

    scanf("%d", &routers);

    printf("Enter cost matrix :\n");

    // Input cost matrix
    for(i = 0; i < routers; i++){

        for(j = 0; j < routers; j++){

            scanf("%d", &costmat[i][j]);

            costmat[i][i] = 0;

            routingTable[i].cost[j] =
                    costmat[i][j];

            routingTable[i].from[j] = j;
        }
    }

    int updated;

    // Distance Vector Algorithm
    do{

        updated = 0;

        for(i = 0; i < routers; i++){

            for(j = 0; j < routers; j++){

                for(k = 0; k < routers; k++){

                    // Shorter path check
                    if(routingTable[i].cost[j] >
                       costmat[i][k] +
                       routingTable[k].cost[j]){

                        routingTable[i].cost[j] =
                                costmat[i][k] +
                                routingTable[k].cost[j];

                        routingTable[i].from[j] = k;

                        updated = 1;
                    }
                }
            }
        }

    }while(updated);

    // Print routing table
    for(i = 0; i < routers; i++){

        printf("\nRouter %d\n", i + 1);

        for(j = 0; j < routers; j++){

            printf("To Router %d ",
                    j + 1);

            printf("via %d ",
                    routingTable[i].from[j] + 1);

            printf("Distance %d\n",
                    routingTable[i].cost[j]);
        }
    }

    return 0;
}