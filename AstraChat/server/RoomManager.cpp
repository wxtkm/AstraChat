#include "RoomManager.h"

RoomManager::RoomManager() {
    rooms["General"] = std::make_shared<Room>("General");
    rooms["Games"] = std::make_shared<Room>("Games");
    rooms["Music"] = std::make_shared<Room>("Music");
}

std::shared_ptr<Room> RoomManager::getRoom(const std::string& name) {
    if (rooms.find(name) != rooms.end())
        return rooms[name];

    return nullptr;
}

std::shared_ptr<Room> RoomManager::createRoom(const std::string& name) {
    if (rooms.find(name) == rooms.end()) {
        rooms[name] = std::make_shared<Room>(name);
    }

    return rooms[name];
}

void RoomManager::removeUserFromAll(const std::shared_ptr<Connection>& user) {
    for (auto& [name, room] : rooms) {
        room->removeUser(user);
    }
}