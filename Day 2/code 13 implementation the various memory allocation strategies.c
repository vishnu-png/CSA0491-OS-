#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 100

// Structure to represent a block of memory
typedef struct {
    int start_address;
    int size;
    int allocated;
} MemoryBlock;

// Function prototypes
void initializeMemory();
void displayMemory();
void firstFit(int process_size);
void bestFit(int process_size);
void worstFit(int process_size);

// Global variables
MemoryBlock memory[MEMORY_SIZE];

int main() {
    initializeMemory();
    displayMemory();

    int choice, process_size;

    do {
        printf("\nMemory Allocation Strategies:\n");
        printf("1. First Fit\n");
        printf("2. Best Fit\n");
        printf("3. Worst Fit\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter size of process to allocate: ");
                scanf("%d", &process_size);
                firstFit(process_size);
                break;
            case 2:
                printf("Enter size of process to allocate: ");
                scanf("%d", &process_size);
                bestFit(process_size);
                break;
            case 3:
                printf("Enter size of process to allocate: ");
                scanf("%d", &process_size);
                worstFit(process_size);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }

        if (choice != 4)
            displayMemory();

    } while (choice != 4);

    return 0;
}

// Initialize memory blocks
void initializeMemory() {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        memory[i].start_address = i;
        memory[i].size = 1;
        memory[i].allocated = 0;
    }
}

// Display memory status
void displayMemory() {
    printf("\nMemory Status:\n");
    printf("Start Address\tSize\tAllocated\n");
    for (int i = 0; i < MEMORY_SIZE; i++) {
        printf("%d\t\t%d\t\t%s\n", memory[i].start_address, memory[i].size, memory[i].allocated ? "Yes" : "No");
    }
}

// First Fit memory allocation strategy
void firstFit(int process_size) {
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (!memory[i].allocated && memory[i].size >= process_size) {
            memory[i].allocated = 1;
            break;
        }
    }
}

// Best Fit memory allocation strategy
void bestFit(int process_size) {
    int best_fit_index = -1;
    int min_remaining_size = MEMORY_SIZE + 1;
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (!memory[i].allocated && memory[i].size >= process_size && memory[i].size - process_size < min_remaining_size) {
            best_fit_index = i;
            min_remaining_size = memory[i].size - process_size;
        }
    }
    if (best_fit_index != -1) {
        memory[best_fit_index].allocated = 1;
    }
}

// Worst Fit memory allocation strategy
void worstFit(int process_size) {
    int worst_fit_index = -1;
    int max_remaining_size = -1;
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (!memory[i].allocated && memory[i].size >= process_size && memory[i].size - process_size > max_remaining_size) {
            worst_fit_index = i;
            max_remaining_size = memory[i].size - process_size;
        }
    }
    if (worst_fit_index != -1) {
        memory[worst_fit_index].allocated = 1;
    }
}
