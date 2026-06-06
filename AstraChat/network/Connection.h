#pragma once

#include <winsock2.h>
#include <string>

class Connection {
public:
    Connection(SOCKET socket);

    SOCKET getSocket();

    std::string receive();

    std::string currentRoom;

    void sendMessage(const std::string& msg);

    bool isAlive();

    void setUsername(const std::string& name);

    std::string getUsername();

private:
    SOCKET socket;

    std::string username;
};