#include "dutch.h"

Dutch::Dutch(int targetMoney, std::shared_ptr<User> recieveUser, std::vector<std::shared_ptr<User>> sendUsers) {
    this->targetMoney = targetMoney;
    this->recieveUser = recieveUser;
    this->sendUsers = sendUsers;
}

int Dutch::getTargetMoney() {
    return this->targetMoney;
}

int Dutch::getSendedMoney() {
    return this->sendedMoney;
}

std::shared_ptr<User> Dutch::getRecieveUser() {
    return this->recieveUser;
}

std::vector<std::shared_ptr<User>> Dutch::getSendUsers() {
    return this->sendUsers;
}

std::vector<std::shared_ptr<User>> Dutch::getSendedUsers() {
    return this->sendedUsers;
}

void Dutch::setSendedUsers(std::vector<std::shared_ptr<User>> sendedUsers) {
    this->sendedUsers = sendedUsers;
}

