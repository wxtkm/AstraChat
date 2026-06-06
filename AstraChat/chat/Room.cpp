#include "Room.h"
#include <algorithm>
#include "../network/Connection.h"

Room::Room() {}

Room::Room(const std::string& name) {
    this->name = name;
}

std::string Room::getName() const {
    return name;
}

void Room::addUser(std::shared_ptr<Connection> user) {
    users.push_back(user);
}

void Room::removeUser(std::shared_ptr<Connection> user) {
    users.erase(
        std::remove(users.begin(), users.end(), user),
        users.end()
    );
}

void Room::broadcast(
    const std::string& message,
    std::shared_ptr<Connection> sender
) {
    for (auto& user : users) {

        if (user == sender)
            continue;

        user->sendMessage(message);
    }
}