// Receiver.cpp
#include <windows.h>
#include <iostream>
#include <string>

int main() {
    HANDLE hPipe;
    char buffer[256];
    DWORD bytesRead;

    hPipe = CreateFile(TEXT("\\\\.\\pipe\\MyPipe"), 
        GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);

    if (hPipe == INVALID_HANDLE_VALUE) {
        std::cout << "Failed to connect to pipe. Error: " << GetLastError() << std::endl;
        return 1;
    }

    std::cout << "Connected to sender. Waiting for messages..." << std::endl;

    while (true) {
        if (!ReadFile(hPipe, buffer, sizeof(buffer), &bytesRead, NULL)) {
            std::cout << "Failed to read data. Error: " << GetLastError() << std::endl;
            break;
        } else {
            std::cout << "Message received: " << buffer << std::endl;
        }
    }

    CloseHandle(hPipe);
    return 0;
}