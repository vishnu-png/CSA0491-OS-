#include <stdio.h>
#include <windows.h>

#define BUFFER_SIZE 512

int main() {
    HANDLE hPipe;
    char buffer[BUFFER_SIZE];
    DWORD dwRead;

    // Create the named pipe
    hPipe = CreateNamedPipe("\\\\.\\pipe\\MyPipe",
                            PIPE_ACCESS_INBOUND,
                            PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
                            1,
                            BUFFER_SIZE,
                            BUFFER_SIZE,
                            0,
                            NULL);

    if (hPipe == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Error creating named pipe.\n");
        return 1;
    }

    printf("Named pipe created. Waiting for connection...\n");

    // Wait for client to connect
    if (!ConnectNamedPipe(hPipe, NULL)) {
        fprintf(stderr, "Error connecting to named pipe.\n");
        CloseHandle(hPipe);
        return 1;
    }

    printf("Client connected. Waiting for data...\n");

    // Read data from the pipe
    if (!ReadFile(hPipe, buffer, BUFFER_SIZE, &dwRead, NULL)) {
        fprintf(stderr, "Error reading from pipe.\n");
        CloseHandle(hPipe);
        return 1;
    }

    printf("Received message from client: %s\n", buffer);

    // Clean up
    CloseHandle(hPipe);

    return 0;
}
