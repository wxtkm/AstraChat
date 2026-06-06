#pragma once

#include <string>

class User {
private:
    std::string username;

public:
    User();

    User(const std::string& username);

    void setUsername(const std::string& username);

    std::string getUsername() const;
};