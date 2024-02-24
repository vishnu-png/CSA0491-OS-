#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char filename[] = "example.txt";
    char buffer[100];

    // Create a file and write some content
    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error creating file");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "This is a test file.\n");
    fprintf(file, "We are testing file management operations.\n");
    fclose(file);
    printf("File created and written successfully.\n");

    // Read content from the file
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }
    printf("File content:\n");
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }
    fclose(file);

    // Append more content to the file
    file = fopen(filename, "a");
    if (file == NULL) {
        perror("Error opening file for appending");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "Appending more content to the file.\n");
    fclose(file);
    printf("\nAdditional content appended to the file.\n");

    // Read content again to see the appended content
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }
    printf("\nFile content after appending:\n");
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }
    fclose(file);

    // Delete the file
    if (remove(filename) == 0) {
        printf("\nFile deleted successfully.\n");
    } else {
        perror("Error deleting file");
        exit(EXIT_FAILURE);
    }

    return 0;
}

