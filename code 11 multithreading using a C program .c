#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 2
#define COUNT_MAX 5

// Function executed by each thread
void *print_numbers(void *thread_id) {
    int tid = *(int *)thread_id;
    
    for (int i = 1; i <= COUNT_MAX; ++i) {
        printf("Thread %d: %d\n", tid, i);
        fflush(stdout); // Flush stdout to ensure immediate output
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Create threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        thread_ids[i] = i;
        int rc = pthread_create(&threads[i], NULL, print_numbers, (void *)&thread_ids[i]);
        if (rc) {
            printf("Error: Unable to create thread %d\n", rc);
            exit(-1);
        }
    }

    // Wait for all threads to complete
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    printf("Main thread exiting.\n");

    return 0;
}
