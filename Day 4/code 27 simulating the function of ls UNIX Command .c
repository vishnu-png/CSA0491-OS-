#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    char *dir_path;

    // If a directory is provided as a command-line argument
    if (argc == 2) {
        dir_path = argv[1];
    } else if (argc == 1) {
        // If no argument is provided, use the current directory
        dir_path = ".";
    } else {
        fprintf(stderr, "Usage: %s [directory]\n", argv[0]);
        return 1;
    }

    DIR *dir = opendir(dir_path);
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dir);
    return 0;
}
