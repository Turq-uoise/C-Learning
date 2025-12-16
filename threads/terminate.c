#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


void child_process(int i){
    sleep(5-i);
    
    printf("I'm the son %d.\n", getpid());
    exit(i);
}

void parent_process(){
    int status;
    pid_t child_pid = wait(&status);
    if WIFEXITED(status){
        printf("I'm the father. My son is %d and his status is %d.\n", child_pid, WEXITSTATUS(status));
    }
}

int main(void){
    for (int i = 0; i < 5; i++){
        pid_t pid = fork();
        if (pid == 0){
            child_process(i);
        }
    }
    for (int i = 0; i < 5; i++){
        parent_process();
    }

    return 0;
}