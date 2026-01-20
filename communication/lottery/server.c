#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>

#define MAX_CLIENTS 10
#define LOTTERY_NUMBERS 11

void send_random_numbers(int client_sds[], int reg_clients) {
    printf("Sending random numbers to clients...\n");
    char message[1024];
    int used[LOTTERY_NUMBERS + 1];
    memset(used, 0, sizeof(used));
    for (int i = 0; i < reg_clients; i++) {
        int random_num;
        do {
            random_num = (rand() % LOTTERY_NUMBERS) + 1;
        } while (used[random_num]);
        used[random_num] = 1;
        sprintf(message, "NUMBER: %d\n", random_num);
        send(client_sds[i], message, strlen(message), 0);
    }
}

void run_lottery(int client_sds[], int reg_clients) {
    printf("Running lottery...\n");
    int winner_num = (rand() % LOTTERY_NUMBERS) + 1;
    char message[1024];
    sprintf(message, "WINNER: %d\n", winner_num);
    for (int i = 0; i < reg_clients; i++) {
        send(client_sds[i], message, strlen(message), 0);
    }
}

int main(void){
    int ret, sd, reg_clients = 0;
    int client_sds[MAX_CLIENTS];
    socklen_t len;
    struct sockaddr_in my_addr, cl_addr;
    sd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&my_addr, 0, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(4242);
    inet_pton(AF_INET, "127.0.0.1", &my_addr.sin_addr);
    ret = bind(sd, (struct sockaddr *)&my_addr, sizeof(my_addr));
    ret = listen(sd, 10);
    printf("Server is running and waiting for clients on port 4242...\n");
    len = sizeof(cl_addr);
    srand(time(NULL));
    while (reg_clients < MAX_CLIENTS) {
        int new_sd = accept(sd, (struct sockaddr *)&cl_addr, &len);
        if (new_sd >= 0) {
            client_sds[reg_clients++] = new_sd;
            printf("Client %d connected.\n", reg_clients);
        }
    }

    send_random_numbers(client_sds, reg_clients);

    printf("Waiting for all clients to acknowledge...\n");
    for (int i = 0; i < reg_clients; i++) {
        char ack[10];
        recv(client_sds[i], ack, sizeof(ack), 0);
        printf("Received ACK from client %d\n", i+1);
    }

    run_lottery(client_sds, reg_clients);
    
    for (int i = 0; i < reg_clients; i++) {
        close(client_sds[i]);
    }
    close(sd);
    
    return 0;
}
//./server & sleep 1; for i in {1..10}; do ./client & done; wait