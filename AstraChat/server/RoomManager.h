#pragma once

#include <unordered_map>
#include <memory>
#include <string>
#include "../chat/Room.h"

class RoomManager {
private:
    std::unordered_map<std::string, std::shared_ptr<Room>> rooms;

public:
    RoomManager();

    std::shared_ptr<Room> getRoom(const std::string& name);

    std::shared_ptr<Room> createRoom(const std::string& name);

    void removeUserFromAll(const std::shared_ptr<Connection>& user);
};