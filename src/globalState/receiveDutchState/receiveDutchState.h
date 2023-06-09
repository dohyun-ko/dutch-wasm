#pragma once
#include <string>
#include <vector>

#include "../../components/state/State.cpp"

class ReceiveDutchState {
    private:
        ReceiveDutchState();
        State<vector<string>>* receiveUUIDsState;
        State<string>* nowUUID;
        static ReceiveDutchState* instance;
    public:
        static ReceiveDutchState* getInstance();
        State<vector<string>>* getReceiveUUIDs();
        State<string>* getNowUUID();
};