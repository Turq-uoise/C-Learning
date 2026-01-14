#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(void){
    int ret, sd, new_sd;
    socklen_t len;
    struct sockaddr_in my_addr, cl_addr;
    sd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&my_addr, 0, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(4242);
    inet_pton(AF_INET, "127.0.0.1", &my_addr.sin_addr);
    ret = bind(sd, (struct sockaddr *)&my_addr, sizeof(my_addr));
    ret = listen(sd, 10);
    len = sizeof(cl_addr);
    new_sd = accept(sd, (struct sockaddr *)&cl_addr, &len);
    
    int fd = open("file.txt", O_RDONLY);
    char buffer[1024];
    ssize_t bytes;
    while ((bytes = read(fd, buffer, sizeof(buffer))) > 0) {
        send(new_sd, buffer, bytes, 0);
    }

    close(fd);
    close(new_sd);
    close(sd);
    
    return 0;
}