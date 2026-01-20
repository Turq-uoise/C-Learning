#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

int main(void){
    int ret, sd;
    socklen_t len;
    struct sockaddr_in my_addr;
    len = sizeof(my_addr);
    char buffer[1024];
    
    sd = socket(AF_INET, SOCK_DGRAM, 0);
    memset(&my_addr, 0, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(4242);
    my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    inet_pton(AF_INET, "127.0.0.1", &my_addr.sin_addr);
    printf("client hello");
    
    for (int i = 0; i < 10; i++) {
        int received_bytes = recvfrom(sd, buffer, 1024, 0, (struct sockaddr*)&my_addr, &len);
        printf("%s", buffer);
    }

    close(sd);
    return 0;
}