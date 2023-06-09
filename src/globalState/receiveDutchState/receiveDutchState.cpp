#include "receiveDutchState.h"

ReceiveDutchState* ReceiveDutchState::instance = nullptr;

ReceiveDutchState::ReceiveDutchState() {
    this->receiveUUIDsState = new State<vector<string>>(vector<string>());
    this->nowUUID = new State<string>("");
}

ReceiveDutchState* ReceiveDutchState::getInstance() {
    if (instance == nullptr) {
        instance = new ReceiveDutchState();
    }
    return instance;
}

State<vector<string>>* ReceiveDutchState::getReceiveUUIDs() {
    return this->receiveUUIDsState;
}

State<string>* ReceiveDutchState::getNowUUID() {
    return this->nowUUID;
}
