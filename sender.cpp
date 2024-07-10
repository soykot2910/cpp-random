// Sender.cpp
#include <windows.h>
#include <iostream>
#include <string>

int main() {
    HANDLE hPipe;
    std::string message;

    hPipe = CreateNamedPipe(TEXT("\\\\.\\pipe\\MyPipe"),
        PIPE_ACCESS_OUTBOUND, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        1, 0, 0, 0, NULL);

    if (hPipe == INVALID_HANDLE_VALUE) {
        std::cout << "Failed to create pipe. Error: " << GetLastError() << std::endl;
        return 1;
    }

    std::cout << "Waiting for receiver..." << std::endl;
    if (!ConnectNamedPipe(hPipe, NULL)) {
        std::cout << "Failed to connect to pipe. Error: " << GetLastError() << std::endl;
        CloseHandle(hPipe);
        return 1;
    }

    std::cout << "Connected to receiver. Type 'exit' to quit." << std::endl;

    while (true) {
        std::cout << "Enter message: ";
        std::getline(std::cin, message);

        if (message == "exit") break;

        DWORD bytesWritten;
        if (!WriteFile(hPipe, message.c_str(), message.size() + 1, &bytesWritten, NULL)) {
            std::cout << "Failed to send data. Error: " << GetLastError() << std::endl;
            break;
        } else {
            std::cout << "Message sent: " << message << std::endl;
        }
    }

    CloseHandle(hPipe);
    return 0;
}