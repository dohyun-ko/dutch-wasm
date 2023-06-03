#include "userState.h"

UserState* UserState::instance = nullptr;

UserState::UserState() {
    this->state = new State<User>(User("","",""));
}

UserState* UserState::getInstance() {
    if (instance == nullptr) {
        instance = new UserState();
    }
    return instance;
}

State<User>* UserState::getState() {
    return this->state;
}

