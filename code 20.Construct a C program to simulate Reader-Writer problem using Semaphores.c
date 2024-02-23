#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 5
#define NUM_WRITERS 2

pthread_mutex_t mutex;
sem_t wrt;
int read_count = 0;
int data = 0;

void *reader(void *arg) {
    int id = *((int *)arg);

    pthread_mutex_lock(&mutex);
    read_count++;
    if (read_count == 1) {
        sem_wait(&wrt); // First reader locks the writer
    }
    pthread_mutex_unlock(&mutex);

    // Reading data
    printf("Reader %d reads data: %d\n", id, data);
    sleep(1); // Simulate reading operation

    pthread_mutex_lock(&mutex);
    read_count--;
    if (read_count == 0) {
        sem_post(&wrt); // Last reader unlocks the writer
    }
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

void *writer(void *arg) {
    int id = *((int *)arg);

    sem_wait(&wrt); // Wait for writer semaphore

    // Writing data
    data++;
    printf("Writer %d writes data: %d\n", id, data);
    sleep(2); // Simulate writing operation

    sem_post(&wrt); // Release writer semaphore

    pthread_exit(NULL);
}

int main() {
    pthread_t reader_threads[NUM_READERS], writer_threads[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];
    int i;

    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt, 0, 1);

    // Create reader threads
    for (i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&reader_threads[i], NULL, reader, &reader_ids[i]);
    }

    // Create writer threads
    for (i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writer_threads[i], NULL, writer, &writer_ids[i]);
    }

    // Join reader threads
    for (i = 0; i < NUM_READERS; i++) {
        pthread_join(reader_threads[i], NULL);
    }

    // Join writer threads
    for (i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writer_threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}
