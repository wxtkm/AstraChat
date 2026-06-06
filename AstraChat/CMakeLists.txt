cmake_minimum_required(VERSION 3.15)

project(AstraChat)

set(CMAKE_CXX_STANDARD 20)

# ===================== SERVER =====================
add_executable(Server
    AstraChat.cpp
    server/Server.cpp
    server/RoomManager.cpp

    network/Connection.cpp

    chat/Room.cpp
    chat/User.cpp

    core/ThreadPool.cpp
    core/Logger.cpp
)

# ===================== CLIENT =====================
add_executable(Client
    client/Client.cpp
)