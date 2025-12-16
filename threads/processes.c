#include <stdio.h>
#include <unistd.h>

void child_process(){
    printf("I'm %d, son of process %d.\n", getpid(), getppid());
}

void parent_process(pid_t pid){
    printf("I'm the father. My son is: %d.\n", pid);
}

int main(void){
    pid_t pid = fork();
    if (pid == 0){
        child_process();
    }
    else{
        parent_process(pid);
    }
    return 0;
}