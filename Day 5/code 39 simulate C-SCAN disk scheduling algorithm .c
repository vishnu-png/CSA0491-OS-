#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 1000
#define MAX_CYLINDERS 5000

void cscan(int requests[], int num_requests, int start, int num_cylinders) {
    int total_head_movements = 0;
    int current_pos = start;

    // Sorting the requests
    for (int i = 0; i < num_requests - 1; i++) {
        for (int j = 0; j < num_requests - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    // Finding the index where the current position lies
    int index = 0;
    for (int i = 0; i < num_requests; i++) {
        if (requests[i] >= current_pos) {
            index = i;
            break;
        }
    }

    printf("C-SCAN Sequence: ");

    // Scanning towards the end
    for (int i = index; i < num_requests; i++) {
        printf("%d ", requests[i]);
        total_head_movements += abs(requests[i] - current_pos);
        current_pos = requests[i];
    }

    // Moving to the beginning
    if (index > 0) {
        total_head_movements += abs(current_pos - num_cylinders);
        current_pos = 0;
        printf("%d ", num_cylinders);
    }

    // Scanning towards the current position
    for (int i = 0; i < index; i++) {
        printf("%d ", requests[i]);
        total_head_movements += abs(requests[i] - current_pos);
        current_pos = requests[i];
    }

    printf("\nTotal Head Movements: %d\n", total_head_movements);
}

int main() {
    int num_requests, start, num_cylinders;
    int requests[MAX_REQUESTS];

    printf("Enter the number of requests: ");
    scanf("%d", &num_requests);

    if (num_requests <= 0 || num_requests > MAX_REQUESTS) {
        printf("Invalid number of requests.\n");
        return 1;
    }

    printf("Enter the cylinder number where the disk head is currently located: ");
    scanf("%d", &start);

    printf("Enter the total number of cylinders on the disk: ");
    scanf("%d", &num_cylinders);

    if (num_cylinders <= 0 || num_cylinders > MAX_CYLINDERS) {
        printf("Invalid number of cylinders.\n");
        return 1;
    }

    printf("Enter the requests: ");
    for (int i = 0; i < num_requests; i++) {
        scanf("%d", &requests[i]);
        if (requests[i] < 0 || requests[i] >= num_cylinders) {
            printf("Invalid request.\n");
            return 1;
        }
    }

    cscan(requests, num_requests, start, num_cylinders);

    return 0;
}
