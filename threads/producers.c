#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_BUFFER 5
#define THREADS 10

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t not_full  = PTHREAD_COND_INITIALIZER;
pthread_cond_t not_empty = PTHREAD_COND_INITIALIZER;

int buffer = 0;

void* producer(void* arg) {
    pthread_mutex_lock(&mutex);

    while (buffer == MAX_BUFFER) {
        pthread_cond_wait(&not_full, &mutex);
    }

    buffer++;
    printf("Producer produced, buffer = %d\n", buffer);

    pthread_cond_signal(&not_empty);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* consumer(void* arg) {
    pthread_mutex_lock(&mutex);

    while (buffer == 0) {
        pthread_cond_wait(&not_empty, &mutex);
    }

    buffer--;
    printf("Consumer consumed, buffer = %d\n", buffer);

    pthread_cond_signal(&not_full);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main(void) {
    pthread_t prod[THREADS], cons[THREADS];

    for (int i = 0; i < THREADS; i++) {
        pthread_create(&prod[i], NULL, producer, NULL);
        pthread_create(&cons[i], NULL, consumer, NULL);
    }

    for (int i = 0; i < THREADS; i++) {
        pthread_join(prod[i], NULL);
        pthread_join(cons[i], NULL);
    }

    return 0;
}
