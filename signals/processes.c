#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

pid_t pids[3];

void signalhit(int signal);

void child_process(){
    printf("I'm %d, son of process %d.\n", getpid(), getppid());
    exit(EXIT_SUCCESS);
}

void child_process2(){
    while (1){
        printf("I'm %d and I'm looping\n", getpid());
        sleep(1);
    }
}

void parent_process(){
    int status;
    pid_t child_pid = wait(&status);
    if (WIFEXITED(status)){
        printf("I'm the father. My son is %d and his status is %d.\n", child_pid, WEXITSTATUS(status));
    }
    sleep(3);
    kill(pids[0], SIGUSR1);
    kill(pids[1], SIGUSR1);
    kill(pids[2], SIGUSR1);
    exit(EXIT_SUCCESS);
}

void signalhit(int signal){
    printf("I am child %d and I recieved signal %d from my parent %d.\n", getpid(), signal, getppid());
    exit(EXIT_FAILURE);
}

int main(void){
    signal(SIGUSR1, signalhit);
    for (int i = 0; i < 3; i++){
        pid_t pid = fork();
        if (pid == 0){
            if (i == 1){
                child_process();
            }
            else {
                child_process2();
            }
        }
        else {
            pids[i] = pid;
        }
    }
    for (int i = 0; i < 5; i++){
        parent_process();
    }
    return 0;
}