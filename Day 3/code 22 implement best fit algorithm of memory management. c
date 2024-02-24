#include <stdio.h>

#define MAX_MEMORY_SIZE 1000

// Structure to represent a memory block
typedef struct {
    int size;
    int allocated;
} MemoryBlock;

// Function to allocate memory using Best Fit Algorithm
void best_fit(MemoryBlock memory[], int num_blocks, int process_size) {
    int best_fit_index = -1;
    int min_fragment = MAX_MEMORY_SIZE + 1;

    // Find the memory block with the best fit
    for (int i = 0; i < num_blocks; i++) {
        if (!memory[i].allocated && memory[i].size >= process_size) {
            if (memory[i].size - process_size < min_fragment) {
                min_fragment = memory[i].size - process_size;
                best_fit_index = i;
            }
        }
    }

    // Allocate memory if a suitable block is found
    if (best_fit_index != -1) {
        memory[best_fit_index].allocated = 1;
        printf("Memory allocated successfully at block %d\n", best_fit_index);
    } else {
        printf("Memory allocation failed: No suitable block found\n");
    }
}

int main() {
    // Initialize memory blocks and process size
    MemoryBlock memory[] = {{100, 0}, {200, 0}, {300, 0}};
    int num_blocks = sizeof(memory) / sizeof(memory[0]);
    int process_size = 150;

    // Call best_fit function to allocate memory using Best Fit Algorithm
    best_fit(memory, num_blocks, process_size);

    return 0;
}
