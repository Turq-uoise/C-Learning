#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <stdbool.h>

sem_t *mutex;
bool reading = false;

void* rwrite(void *arg){
    sem_wait(mutex);
    reading = false;
    printf("Writing...\n");
    sleep(1);
    printf("Stopped Writing...\n");
    sem_post(mutex);
    pthread_exit(NULL);
}

void* wread(void *arg){
    printf("Reading: %d\n", reading);
    if (reading == true){
        printf("Second Reading...\n");
        sleep(1);
        printf("Stopped Reading...\n");
        reading = false;
    }
    else {
        sem_wait(mutex); // Both readings stop here
        if (reading == true){
            printf("Second Reading!\n");
        }
        reading = true; // When the first reading sets value to true, the second reading is not updated to go through the true loop
        printf("First Reading...\n");
        sleep(1);
        printf("Stopped Reading...\n");
        reading = false;
        sem_post(mutex);
    }
    
    pthread_exit(NULL);
}

int main(void){
    if (sem_unlink("/mutex")) {
        perror("sem_unlink");
        return EXIT_FAILURE;
    }
    if ((mutex = sem_open("/mutex", O_CREAT, 0644, 1)) == SEM_FAILED) {
        perror("failed to open semaphore");
        return EXIT_FAILURE;
    }
   
    pthread_t t1, t2, t3, t4;
    printf("%d\n", reading);
    pthread_create(&t1, NULL, rwrite, NULL);
    pthread_create(&t2, NULL, wread, NULL);
    pthread_create(&t3, NULL, wread, NULL);
    pthread_create(&t4, NULL, rwrite, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    sem_close(mutex);

    return 0;
}