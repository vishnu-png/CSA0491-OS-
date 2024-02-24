#include <stdio.h>
#include <stdlib.h>

// Structure to represent a disk block
struct DiskBlock {
    int blockNumber;
    struct DiskBlock *next;
};

// Structure to represent a file
struct File {
    int fileNumber;
    struct DiskBlock *firstBlock;
    struct DiskBlock *lastBlock;
};

// Function to allocate a block for a file
void allocateBlock(struct File *file, int blockNumber) {
    struct DiskBlock *newBlock = (struct DiskBlock *)malloc(sizeof(struct DiskBlock));
    if (newBlock == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    newBlock->blockNumber = blockNumber;
    newBlock->next = NULL;

    if (file->firstBlock == NULL) {
        // First block of the file
        file->firstBlock = newBlock;
        file->lastBlock = newBlock;
    } else {
        // Append block to the end of the file
        file->lastBlock->next = newBlock;
        file->lastBlock = newBlock;
    }
    printf("Block %d allocated to file %d\n", blockNumber, file->fileNumber);
}

// Function to deallocate blocks of a file
void deallocateBlocks(struct File *file) {
    struct DiskBlock *currentBlock = file->firstBlock;
    while (currentBlock != NULL) {
        struct DiskBlock *temp = currentBlock;
        currentBlock = currentBlock->next;
        free(temp);
    }
    file->firstBlock = NULL;
    file->lastBlock = NULL;
    printf("Blocks deallocated for file %d\n", file->fileNumber);
}

int main() {
    // Simulating 5 files
    struct File files[5];

    // Initialize files
    for (int i = 0; i < 5; ++i) {
        files[i].fileNumber = i + 1;
        files[i].firstBlock = NULL;
        files[i].lastBlock = NULL;
    }

    // Allocate blocks for files
    allocateBlock(&files[0], 1);
    allocateBlock(&files[0], 2);
    allocateBlock(&files[1], 3);
    allocateBlock(&files[1], 4);
    allocateBlock(&files[1], 5);

    // Deallocate blocks for files
    deallocateBlocks(&files[0]);
    deallocateBlocks(&files[1]);

    return 0;
}
