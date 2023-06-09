#include "user.h"

User::User(std::string UUID, std::string username, std::string email) {
    this->UUID = UUID;
    this->username = username;
    this->email = email;
}

std::string User::getUUID() {
    return this->UUID;
}

std::string User::getUsername() {
    return this->username;
}

std::string User::getEmail() {
    return this->email;
}
