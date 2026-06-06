#include "User.h"

User::User() {}

User::User(const std::string& username) {
    this->username = username;
}

void User::setUsername(const std::string& username) {
    this->username = username;
}

std::string User::getUsername() const {
    return username;
}