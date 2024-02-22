#include <stdio.h>
#include <windows.h>

#define BUFSIZE 4096

int main()
{
    HANDLE hPipe;
    char buffer[BUFSIZE];
    DWORD dwRead;

    // Create the named pipe
    hPipe = CreateNamedPipe(TEXT("\\\\.\\pipe\\my_pipe"),
                            PIPE_ACCESS_DUPLEX,
                            PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
                            PIPE_UNLIMITED_INSTANCES,
                            BUFSIZE,
                            BUFSIZE,
                            0,
                            NULL);

    if (hPipe == INVALID_HANDLE_VALUE)
    {
        printf("Error creating named pipe\n");
        return 1;
    }

    // Wait for a client to connect
    if (!ConnectNamedPipe(hPipe, NULL))
    {
        printf("Error connecting to client\n");
        CloseHandle(hPipe);
        return 1;
    }

    // Read data from the pipe
    if (!ReadFile(hPipe, buffer, BUFSIZE, &dwRead, NULL))
    {
        printf("Error reading from pipe\n");
        CloseHandle(hPipe);
        return 1;
    }

    printf("Received message from client: %s\n", buffer);

    // Close the pipe handle
    CloseHandle(hPipe);

    return 0;
}
