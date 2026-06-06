#include <iostream>
#include "server/Server.h"

int main() {
    std::cout << "AstraChat starting..." << std::endl;

    Server server;
    server.start();

    return 0;
}