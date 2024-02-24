#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 50

void worstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    int i, j;

    for (i = 0; i < n; i++)
        allocation[i] = -1;

    for (i = 0; i < n; i++) {
        int worstFitIdx = -1;
        for (j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstFitIdx == -1 || blockSize[j] > blockSize[worstFitIdx])
                    worstFitIdx = j;
            }
        }

        if (worstFitIdx != -1) {
            allocation[i] = worstFitIdx;
            blockSize[worstFitIdx] -= processSize[i];
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for (i = 0; i < n; i++) {
        printf(" %d \t\t %d \t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

int main() {
    int blockSize[MAX_BLOCKS], processSize[MAX_BLOCKS];
    int m, n, i;

    printf("Enter the number of memory blocks: ");
    scanf("%d", &m);
    printf("Enter the size of each memory block:\n");
    for (i = 0; i < m; i++)
        scanf("%d", &blockSize[i]);

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the size of each process:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &processSize[i]);

    worstFit(blockSize, m, processSize, n);

    return 0;
}
