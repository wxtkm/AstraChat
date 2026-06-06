#include "Connection.h"
#include <winsock2.h>
#include <iostream>

Connection::Connection(SOCKET socket) {
    this->socket = socket;
}

SOCKET Connection::getSocket() {
    return socket;
}

std::string Connection::receive() {
    char buffer[1024];
    ZeroMemory(buffer, 1024);

    int bytes = recv(socket, buffer, 1024, 0);

    if (bytes <= 0) {
        return "";
    }

    return std::string(buffer, bytes);
}

void Connection::sendMessage(const std::string& msg) {
    send(socket, msg.c_str(), msg.size(), 0);
}

bool Connection::isAlive() {
    char test;
    int result = recv(socket, &test, 1, MSG_PEEK);
    return result > 0;
}

void Connection::setUsername(const std::string& name) {
    username = name;
}

std::string Connection::getUsername() {
    return username;
}