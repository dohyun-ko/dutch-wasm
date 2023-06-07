#include "sendDutchState.h"

SendDutchState* SendDutchState::instance = nullptr;

SendDutchState::SendDutchState() {
    this->sendUUIDsState = new State<vector<string>>(vector<string>());
    this->nowUUID = new State<string>("");
}

SendDutchState* SendDutchState::getInstance() {
    if (instance == nullptr) {
        instance = new SendDutchState();
    }
    return instance;
}

State<vector<string>>* SendDutchState::getSendUUIDs() {
    return this->sendUUIDsState;
}

State<string>* SendDutchState::getNowUUID() {
    return this->nowUUID;
}