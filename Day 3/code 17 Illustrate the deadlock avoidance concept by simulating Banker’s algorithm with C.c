#include <stdio.h>

// Function to check if the requested resources can be allocated
int isSafe(int processes[], int available[], int max[][4], int allocation[][4], int need[][4], int n, int m) {
    int finish[n];
    int work[m];
    int i, j;
    
    // Initialize work and finish arrays
    for (i = 0; i < m; i++)
        work[i] = available[i];
    for (i = 0; i < n; i++)
        finish[i] = 0;

    int count = 0;
    int safeSeq[n];

    while (count < n) {
        int found = 0;
        for (i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int j;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j])
                        break;
                }
                if (j == m) {
                    for (int k = 0; k < m; k++)
                        work[k] += allocation[i][k];
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (found == 0) {
            printf("System is not in safe state\n");
            return 0;
        }
    }
    
    printf("System is in safe state.\nSafe sequence is: ");
    for (i = 0; i < n; i++)
        printf("%d ", safeSeq[i]);
    printf("\n");
    
    return 1;
}

int main() {
    int processes[] = {0, 1, 2, 3, 4};
    int available[] = {1, 5, 2, 0};
    int max[][4] = {
        {0, 0, 1, 2},
        {1, 7, 5, 0},
        {2, 3, 5, 6},
        {0, 6, 5, 2},
        {0, 6, 5, 6}
    };
    int allocation[][4] = {
        {0, 0, 1, 2},
        {1, 0, 0, 0},
        {1, 3, 5, 4},
        {0, 6, 3, 2},
        {0, 0, 1, 4}
    };
    int need[5][4];
    int i, j;
    
    int n = sizeof(processes) / sizeof(processes[0]);
    int m = sizeof(available) / sizeof(available[0]);

    // Calculating need matrix
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - allocation[i][j];

    // Check for safe state and get safe sequence if possible
    isSafe(processes, available, max, allocation, need, n, m);

    return 0;
}
