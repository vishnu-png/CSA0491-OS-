#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t forks[NUM_PHILOSOPHERS];
pthread_t philosophers[NUM_PHILOSOPHERS];

void* philosopher(void* arg) {
    int id = *((int*)arg);
    int left_fork = id;
    int right_fork = (id + 1) % NUM_PHILOSOPHERS;

    // Try to pick up left fork
    pthread_mutex_lock(&forks[left_fork]);
    printf("Philosopher %d picks up left fork %d\n", id, left_fork);

    // Try to pick up right fork
    pthread_mutex_lock(&forks[right_fork]);
    printf("Philosopher %d picks up right fork %d and eats\n", id, right_fork);
    // Eating...
    usleep(1000000); // Sleep for 1 second to simulate eating
    printf("Philosopher %d puts down right fork %d\n", id, right_fork);
    pthread_mutex_unlock(&forks[right_fork]);

    printf("Philosopher %d puts down left fork %d and thinks\n", id, left_fork);
    pthread_mutex_unlock(&forks[left_fork]);

    return NULL;
}

int main() {
    int i;
    int ids[NUM_PHILOSOPHERS];

    // Initialize mutex locks for forks
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    // Create philosopher threads
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    // Join philosopher threads
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy mutex locks
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}
