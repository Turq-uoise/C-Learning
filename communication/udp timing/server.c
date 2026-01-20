#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>


int main(void){
    int ret, sd;
    socklen_t len;
    struct sockaddr_in my_addr, cl_addr;
    socklen_t addrlen = sizeof(cl_addr);
    sd = socket(AF_INET, SOCK_DGRAM, 0);
    memset(&my_addr, 0, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(4242);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    //inet_pton(AF_INET, "127.0.0.1", &my_addr.sin_addr);
    ret = bind(sd, (struct sockaddr *)&my_addr, sizeof(my_addr));


    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char time_sent[1024];
    int length = sprintf(time_sent, "now: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    printf("Client started at %s: %d\n", time_sent, length);

    while(1){
        sendto(sd, time_sent, length, 0, (struct sockaddr*)&cl_addr, addrlen);
        sleep(5);
    }

    close(sd);
    
    return 0;
}