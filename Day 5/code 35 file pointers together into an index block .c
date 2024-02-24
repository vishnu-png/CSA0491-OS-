#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_FILES 100
#define MAX_BLOCKS 1000
#define BLOCK_SIZE 512

typedef struct {
    int block_pointers[MAX_BLOCKS];
    int num_blocks;
} IndexBlock;

typedef struct {
    int index_block_pointer;
    int file_size;
    bool is_allocated;
} File;

IndexBlock index_block;
File files[MAX_FILES];

void initialize() {
    for (int i = 0; i < MAX_BLOCKS; ++i)
        index_block.block_pointers[i] = -1;

    index_block.num_blocks = 0;

    for (int i = 0; i < MAX_FILES; ++i) {
        files[i].index_block_pointer = -1;
        files[i].file_size = 0;
        files[i].is_allocated = false;
    }
}

int allocate_blocks(int num_blocks) {
    if (index_block.num_blocks + num_blocks > MAX_BLOCKS) {
        printf("Error: Not enough space to allocate %d blocks.\n", num_blocks);
        return -1;
    }

    int start_index = index_block.num_blocks;
    index_block.num_blocks += num_blocks;

    return start_index;
}

void deallocate_blocks(int start_index, int num_blocks) {
    // Just mark blocks as deallocated, actual implementation might release resources
    for (int i = start_index; i < start_index + num_blocks; ++i) {
        index_block.block_pointers[i] = -1;
    }
}

int create_file(int file_size) {
    int num_blocks_needed = (file_size + BLOCK_SIZE - 1) / BLOCK_SIZE;
    int start_index = allocate_blocks(num_blocks_needed);

    if (start_index != -1) {
        for (int i = 0; i < MAX_FILES; ++i) {
            if (!files[i].is_allocated) {
                files[i].index_block_pointer = start_index;
                files[i].file_size = file_size;
                files[i].is_allocated = true;
                return i;
            }
        }
    }

    printf("Error: Cannot create file, no space available.\n");
    return -1;
}

void delete_file(int file_id) {
    if (file_id < 0 || file_id >= MAX_FILES || !files[file_id].is_allocated) {
        printf("Error: Invalid file ID.\n");
        return;
    }

    int start_index = files[file_id].index_block_pointer;
    int num_blocks = (files[file_id].file_size + BLOCK_SIZE - 1) / BLOCK_SIZE;
    deallocate_blocks(start_index, num_blocks);

    files[file_id].index_block_pointer = -1;
    files[file_id].file_size = 0;
    files[file_id].is_allocated = false;
}

int main() {
    initialize();

    int file1 = create_file(1024); // Creating a file of size 1024 bytes
    int file2 = create_file(512);  // Creating a file of size 512 bytes

    if (file1 != -1 && file2 != -1) {
        printf("Files created successfully.\n");
        printf("File 1 ID: %d\n", file1);
        printf("File 2 ID: %d\n", file2);
    }

    // Simulating file deletion
    delete_file(file1);
    printf("File 1 deleted.\n");

    return 0;
}
