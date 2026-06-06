# AstraChat

AstraChat is a real-time C++ TCP chat server featuring a room-based system, multithreaded architecture, and command-driven user interaction.

The project demonstrates backend fundamentals such as socket programming, concurrency, room management, and scalable server design.

---

## Features

- TCP-based client-server architecture (Winsock)
- Real-time messaging between multiple clients
- Room system (General, Games, Music + custom rooms)
- Create and join chat rooms dynamically
- Return to default room (General)
- Username system per connection
- Multithreaded client handling
- Message broadcasting inside rooms
- Basic server-side logging system
- CMake-based build system

---

## Architecture

```
Client <---- TCP ----> Server
|
├── RoomManager
├── Rooms (General / custom)
├── Connection wrapper
├── Logger
└── Thread per client
```

---

## Commands

Inside chat:

```
/join <room> - join existing room
/create <room> - create new room
/leave - return to General
```

---

## Tech Stack

- C++20
- Winsock2 (Windows sockets API)
- Multithreading (std::thread)
- Mutex synchronization
- CMake build system

---

## How to Run

```
1. Build
bash
cmake -S . -B build
cmake --build build

2. Run server
Server.exe

3. Run client(s)
Client.exe

Future Improvements
Thread pool architecture (instead of per-thread client model)
Async I/O (IOCP / Boost.Asio)
Authentication system
Private messages (DMs)
Message history storage
WebSocket version
```

## Author

Built as a backend learning project focused on systems programming and network architecture in C++.