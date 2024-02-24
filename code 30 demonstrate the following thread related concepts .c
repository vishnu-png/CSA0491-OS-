#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *thread_function(void *arg) {
    printf("Hello from a thread!\n");
    return NULL;
}

int main() {
    pthread_t tid1, tid2;
    
    // Creating two threads
    pthread_create(&tid1, NULL, thread_function, NULL);
    pthread_create(&tid2, NULL, thread_function, NULL);
    
    // Joining threads
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    
    // Checking if threads are equal
    printf("Checking if two threads are equal: %s\n", pthread_equal(tid1, tid2) ? "true" : "false");
    
    // Exiting threads
    pthread_exit(NULL);
    
    printf("This line won't be reached.\n");
    return 0;
}
