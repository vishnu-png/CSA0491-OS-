#include<stdio.h>
#include<stdlib.h>

void fcfs(int *requests, int n, int head) {
    int total_seek_time = 0;
    int current_track = head;

    printf("Sequence of disk accesses:\n");
    for (int i = 0; i < n; i++) {
        printf("%d -> ", current_track);
        total_seek_time += abs(current_track - requests[i]);
        current_track = requests[i];
    }
    printf("\n");

    printf("Total seek time: %d\n", total_seek_time);
}

int main() {
    int n, head;
    
    printf("Enter the number of requests: ");
    scanf("%d", &n);
    
    int *requests = (int *)malloc(n * sizeof(int));
    
    printf("Enter the request queue: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }
    
    printf("Enter the initial head position: ");
    scanf("%d", &head);
    
    fcfs(requests, n, head);
    
    free(requests);
    
    return 0;
}
