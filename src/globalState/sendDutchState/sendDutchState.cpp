#include "sendDutchState.h"

SendDutchState* SendDutchState::instance = nullptr;

SendDutchState::SendDutchState() {
    this->state = new State<vector<string>>(vector<string>());
}

SendDutchState* SendDutchState::getInstance() {
    if (instance == nullptr) {
        instance = new SendDutchState();
    }
    return instance;
}

State<vector<string>>* SendDutchState::getState() {
    return this->state;
}