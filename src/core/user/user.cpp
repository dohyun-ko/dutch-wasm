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

std::shared_ptr<Dutch> User::makeDutch(int targetMoney, std::vector<std::shared_ptr<User>> sendUsers) {
    return std::make_shared<Dutch>(targetMoney, std::make_shared<User>(*this), sendUsers);
}

