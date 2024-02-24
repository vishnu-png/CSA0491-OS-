#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 100
#define MAX_FILENAME_LENGTH 50
#define DIRECTORY_NAME "organized_files"

void organizeFiles(int numFiles, char filenames[][MAX_FILENAME_LENGTH]);

int main() {
    int numFiles;
    char filenames[MAX_FILES][MAX_FILENAME_LENGTH];

    printf("Enter the number of files: ");
    scanf("%d", &numFiles);

    if (numFiles > MAX_FILES) {
        printf("Exceeded maximum number of files.\n");
        return 1;
    }

    printf("Enter the filenames:\n");
    for (int i = 0; i < numFiles; i++) {
        scanf("%s", filenames[i]);
    }

    organizeFiles(numFiles, filenames);

    printf("Files have been organized.\n");

    return 0;
}

void organizeFiles(int numFiles, char filenames[][MAX_FILENAME_LENGTH]) {
    // Create a directory named "organized_files"
    system("mkdir organized_files");

    // Move each file into the directory
    for (int i = 0; i < numFiles; i++) {
        char moveCommand[MAX_FILENAME_LENGTH + 50]; // +50 for additional characters in the command
        sprintf(moveCommand, "mv %s %s/", filenames[i], DIRECTORY_NAME);
        system(moveCommand);
    }
}
