#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIRS 100
#define MAX_FILES_PER_DIR 100
#define MAX_FILENAME_LEN 50
#define MAX_DIRNAME_LEN 50

// Structure to represent a file
typedef struct {
    char name[MAX_FILENAME_LEN];
} File;

// Structure to represent a directory
typedef struct {
    char name[MAX_DIRNAME_LEN];
    File files[MAX_FILES_PER_DIR];
    int num_files;
} Directory;

// Structure to represent the file system
typedef struct {
    Directory directories[MAX_DIRS];
    int num_dirs;
} FileSystem;

// Function to create a new directory
void createDirectory(FileSystem *fs, const char *dirname) {
    if (fs->num_dirs >= MAX_DIRS) {
        printf("Cannot create directory. Maximum directory limit reached.\n");
        return;
    }
    
    strcpy(fs->directories[fs->num_dirs].name, dirname);
    fs->directories[fs->num_dirs].num_files = 0;
    fs->num_dirs++;
    printf("Directory '%s' created successfully.\n", dirname);
}

// Function to list all directories
void listDirectories(FileSystem *fs) {
    printf("Directories:\n");
    for (int i = 0; i < fs->num_dirs; i++) {
        printf("%s\n", fs->directories[i].name);
    }
}

// Function to add a file to a directory
void addFile(FileSystem *fs, const char *dirname, const char *filename) {
    for (int i = 0; i < fs->num_dirs; i++) {
        if (strcmp(fs->directories[i].name, dirname) == 0) {
            if (fs->directories[i].num_files >= MAX_FILES_PER_DIR) {
                printf("Cannot add file. Maximum file limit reached for directory '%s'.\n", dirname);
                return;
            }
            strcpy(fs->directories[i].files[fs->directories[i].num_files].name, filename);
            fs->directories[i].num_files++;
            printf("File '%s' added to directory '%s' successfully.\n", filename, dirname);
            return;
        }
    }
    printf("Directory '%s' not found.\n", dirname);
}

// Main function
int main() {
    FileSystem fs;
    fs.num_dirs = 0;

    createDirectory(&fs, "Documents");
    createDirectory(&fs, "Pictures");
    createDirectory(&fs, "Music");

    addFile(&fs, "Documents", "Report.docx");
    addFile(&fs, "Documents", "Notes.txt");
    addFile(&fs, "Pictures", "Family.jpg");

    listDirectories(&fs);

    return 0;
}
