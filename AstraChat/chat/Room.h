#pragma once

#include <string>
#include <vector>
#include <memory>

class Connection;

class Room {
private:
    std::string name;
    std::vector<std::shared_ptr<Connection>> users;

public:
    Room();
    Room(const std::string& name);

    std::string getName() const;

    void addUser(std::shared_ptr<Connection> user);

    void removeUser(std::shared_ptr<Connection> user);

    void broadcast(
        const std::string& message,
        std::shared_ptr<Connection> sender
    );
};