#include "userState.h"

UserState* UserState::instance = nullptr;

UserState::UserState() {
    this->currentUser = new State<User>(User("","",""));
    this->loginState = new State<string>("Login");
}

UserState* UserState::getInstance() {
    if (instance == nullptr) {
        instance = new UserState();
    }
    return instance;
}

State<User>* UserState::getCurrentUser() {
    return this->currentUser;
}

State<string>* UserState::getLoginState() {
    return this->loginState;
}

