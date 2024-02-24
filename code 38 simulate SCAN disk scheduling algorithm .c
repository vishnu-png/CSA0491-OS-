#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

void sort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n, head, i, total_seek_time = 0;
    int requests[MAX_REQUESTS];

    printf("Enter total number of requests: ");
    scanf("%d", &n);

    printf("Enter the requests: ");
    for (i = 0; i < n; i++)
        scanf("%d", &requests[i]);

    printf("Enter the initial position of the head: ");
    scanf("%d", &head);

    // Sort the requests to make scanning easier
    sort(requests, n);

    int start_index = 0;
    for (i = 0; i < n; i++) {
        if (requests[i] >= head) {
            start_index = i;
            break;
        }
    }

    printf("Sequence of head movement:\n");
    printf("%d ", head);

    // Scanning towards the higher cylinders
    for (i = start_index; i < n; i++) {
        printf("%d ", requests[i]);
        total_seek_time += abs(requests[i] - head);
        head = requests[i];
    }

    // Scanning towards the lower cylinders
    for (i = start_index - 1; i >= 0; i--) {
        printf("%d ", requests[i]);
        total_seek_time += abs(requests[i] - head);
        head = requests[i];
    }

    printf("\nTotal seek time: %d\n", total_seek_time);

    return 0;
}
