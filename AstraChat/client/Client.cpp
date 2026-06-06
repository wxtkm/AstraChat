#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>
#include <thread>

#pragma comment(lib, "ws2_32.lib")

void receiveLoop(SOCKET sock) {

    char buffer[1024];

    while (true) {

        int bytes = recv(sock, buffer, sizeof(buffer) - 1, 0);

        if (bytes <= 0) {
            std::cout << "[-] Disconnected from server\n";
            break;
        }

        buffer[bytes] = '\0';

        std::cout << buffer << std::endl;
    }
}

int main() {

    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(54000);

    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == 0) {
        std::cout << "[+] Connected to server!\n";

        std::string username;

        std::cout << "Enter username: ";
        std::getline(std::cin, username);

        send(clientSocket, username.c_str(), username.size(), 0);
    }
    else {
        std::cout << "[-] Failed to connect\n";
        return 1;
    }

    std::thread(receiveLoop, clientSocket).detach();

    while (true) {

        std::string msg;
        std::getline(std::cin, msg);

        send(clientSocket, msg.c_str(), msg.size(), 0);
    }

    closesocket(clientSocket);
    WSACleanup();
}