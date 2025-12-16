#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define NUM_THREADS 12

int cont = 0;

void *test(void *num){
    for (int i = 0; i < 1000; i++){
        cont++;
        printf("I'm thread %d and my value is %d\n", *(int *) num, cont);
        // sleep(*(int *) num); // task 1.2
    }
    pthread_exit(NULL);
}

int main(void){
    pthread_t threads[NUM_THREADS];
    int return_code;
    int t;
    int *task_ids[NUM_THREADS];
    for (t=0; t < NUM_THREADS; t++){
        task_ids[t] = (int *) malloc(sizeof(int));
        *task_ids[t] = t;
        
        return_code = pthread_create(&threads[t], NULL, test, (void*) task_ids[t]);
        if (return_code){
            printf("ERRO");
            exit(-1);
        }
    }
    // int joined = pthread_join(threads[1], NULL); // task 1.2
    // printf("%s\n", joined==0?"Success!":"Failure!"); // task 1.2
    pthread_exit(NULL);

    return 0;
}