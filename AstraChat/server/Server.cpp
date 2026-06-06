#include "Server.h"
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>
#include <memory>
#include "RoomManager.h"

#include "../network/Connection.h"
#include "../chat/Room.h"
#include "../chat/User.h"
#include "../core/Logger.h"
#include "../core/ThreadPool.h"

#pragma comment(lib, "ws2_32.lib")

Room generalRoom("General");
RoomManager roomManager;

void printColoredBanner() {
    std::cout << "\033[1;34m";
    std::cout << R"(
                     .---.
                    /     \
                   /   ^   \
                  /   / \   \
                 /   /   \   \
                /   /_.-._\   \
               /  _.-'   '-._  \
              //-'           '-\\
    )" << std::endl;

    std::cout << "\033[1;32m";
    std::cout << R"(
   ___        _             _---_        _       _   
  / _ \  ___ | |_  _ __  _ /  _  \  ___ | |__   | |_ 
 / /_\ \/ __|| __|| '__|(_)| / \ | / __|| '_ \  | __|
/ |  |  \__ \| |_ | |    _ | \_/ || (__ | | | | | |_ 
\ \__/ /|___/ \__||_|   (_)_\___/ \___||_| |_|  \__|
    \_/                    
)" << std::endl;

    std::cout << "\033[0m";
    std::cout << "\n[+] AstraChat Engine Loaded...\n";
}

void handleClient(std::shared_ptr<Connection> client) {

    SOCKET sock = client->getSocket();

    std::string username = client->receive();

    if (username.empty()) {
        Logger::warning("Empty username");
        return;
    }

    client->setUsername(username);

    User user(username);
    Logger::info("User joined: " + user.getUsername());

    auto room = roomManager.getRoom("General");

    if (!room) {
        Logger::error("General room not found!");
        return;
    }

    room->addUser(client);
    client->currentRoom = "General";

    while (true) {

        std::string msg = client->receive();

        if (msg.empty()) {
            Logger::warning("Client disconnected");
            break;
        }

        if (msg.rfind("/create", 0) == 0) {

            std::string roomName = msg.substr(8);

            if (roomName.empty()) {
                client->sendMessage("Usage: /create <room>");
                continue;
            }

            if (roomName == "General" || roomName == "Games" || roomName == "Music") {
                client->sendMessage("You cannot create system room");
                continue;
            }

            auto room = roomManager.createRoom(roomName);

            roomManager.removeUserFromAll(client);
            room->addUser(client);

            client->currentRoom = roomName;

            client->sendMessage("Created and joined: " + roomName);
            continue;
        }

        if (msg.rfind("/join", 0) == 0) {

            std::string roomName = msg.substr(6);

            if (roomName == "General") {
                client->sendMessage("Use /leave to go back to General");
                continue;
            }

            auto newRoom = roomManager.getRoom(roomName);

            if (!newRoom) {
                client->sendMessage("Room not found");
                continue;
            }

            roomManager.removeUserFromAll(client);
            newRoom->addUser(client);

            client->currentRoom = roomName;

            client->sendMessage("Joined room: " + roomName);
            continue;
        }

        if (msg == "/leave") {

            auto general = roomManager.getRoom("General");

            roomManager.removeUserFromAll(client);
            general->addUser(client);

            client->currentRoom = "General";

            client->sendMessage("Returned to General");
            continue;
        }

        std::string formatted = "[" + client->currentRoom + "] "
            + client->getUsername() + ": " + msg;

        Logger::info("Message: " + formatted);

        auto currentRoom = roomManager.getRoom(client->currentRoom);

        if (currentRoom) {
            currentRoom->broadcast(formatted, client);
        }
    }

    roomManager.removeUserFromAll(client);

    closesocket(sock);
}
void Server::start() {

    ThreadPool pool(4);

    printColoredBanner();

    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(54000);

    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, SOMAXCONN);

    Logger::info("Server listening on port 54000");

    while (true) {

        SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);

        if (clientSocket == INVALID_SOCKET)
            continue;

        auto client = std::make_shared<Connection>(clientSocket);

        client->sendMessage("ENTER_USERNAME");

        Logger::info("Client connected");

        pool.enqueue([client]() {
            handleClient(client);
            });
    }

    closesocket(serverSocket);
    WSACleanup();
}