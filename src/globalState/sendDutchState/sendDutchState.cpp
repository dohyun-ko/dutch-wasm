#include "sendDutchState.h"

SendDutchState* SendDutchState::instance = nullptr;

SendDutchState::SendDutchState() {
    this->sendUUIDsState = new State<vector<string>>(vector<string>());
    this->nowUUID = new State<string>("");
    this->dutchType = new State<string>("");
}

SendDutchState* SendDutchState::getInstance() {
    if (instance == nullptr) {
        instance = new SendDutchState();
    }
    return instance;
}

SendDutchState::~SendDutchState() {
    delete this->sendUUIDsState;
    delete this->nowUUID;
    delete this->dutchType;
}

State<vector<string>>* SendDutchState::getSendUUIDs() {
    return this->sendUUIDsState;
}

State<string>* SendDutchState::getNowUUID() {
    return this->nowUUID;
}

State<string>* SendDutchState::getdutchType() {
    return this->dutchType;
}