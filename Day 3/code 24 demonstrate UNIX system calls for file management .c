#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    char buffer[255];

    // Open a file
    fd = open("testfile.txt", O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Write to the file
    write(fd, "Hello, World!", 13);

    // Read from the file
    lseek(fd, 0, SEEK_SET);
    read(fd, buffer, 13);
    printf("Content of file: %s\n", buffer);

    // Close the file
    close(fd);

    return 0;
}
