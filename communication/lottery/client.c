#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(void){
    int ret, sd;
    struct sockaddr_in my_addr;
    char buffer[1024];
    int my_number = -1;
    int winner = -1;
    
    sd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&my_addr, 0, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(4242);
    inet_pton(AF_INET, "127.0.0.1", &my_addr.sin_addr);
    ret = connect(sd, (struct sockaddr *)&my_addr, sizeof(my_addr));
    
    if(ret == 0) {
        while((ret = recv(sd, buffer, sizeof(buffer) - 1, 0)) > 0) {
            buffer[ret] = '\0';
            if(strncmp(buffer, "NUMBER:", 7) == 0) {
                my_number = atoi(buffer + 7);
                printf("Received my number: %d\n", my_number);
                send(sd, "ACK\n", 4, 0);
            } else if(strncmp(buffer, "WINNER:", 7) == 0) {
                winner = atoi(buffer + 7);
                if(my_number == winner) {
                    printf("Success! You won with number %d\n", my_number);
                } else {
                    printf("Fail! Your number %d did not win. Winner was %d\n", my_number, winner);
                }
                break;
            }
        }
    }
    close(sd);
    return 0;
}