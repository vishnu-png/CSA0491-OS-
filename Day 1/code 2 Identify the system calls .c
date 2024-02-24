#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

int main() {
    const char *sourcefile ="C:\\Users\\ecute\\OneDrive\\Desktop\\aj.txt";
    const char *destination_file ="C:\\Users\\ecute\\OneDrive\\Desktop\\ajay.txt";
    // Open source file for reading
    int source_fd = open(sourcefile, O_RDONLY);
    if (source_fd == -1) {
        perror("Error opening source file");
        return 1;
    }

    // Create or open destination file for writing
    int dest_fd = open(destination_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (dest_fd == -1) {
        perror("Error opening destination file");
        close(source_fd);
        return 1;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytesRead, bytesWritten;

    // Read from source file and write to destination file
    while ((bytesRead = read(source_fd, buffer, BUFFER_SIZE)) > 0) {
        bytesWritten = write(dest_fd, buffer, bytesRead);
        if (bytesWritten != bytesRead) {
            perror("Error writing to destination file");
            close(source_fd);
            close(dest_fd);
            return 1;
        }
    }

    // Check for read error
    if (bytesRead == -1) {
        perror("Error reading from source file");
        close(source_fd);
        close(dest_fd);
        return 1;
    }

    // Close file descriptors
    close(source_fd);
    close(dest_fd);

    printf("File copied successfully.\n");
    return 0;
}
