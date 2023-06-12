#pragma once
#include <string>
#include <vector>

#include "../../components/state/State.cpp"

class SendDutchState {
    private:
        SendDutchState();
        State<vector<string>>* sendUUIDsState;
        State<string>* nowUUID;
        State<string>* dutchType;
        static SendDutchState* instance;
    public:
        static SendDutchState* getInstance();
        ~SendDutchState();
        State<vector<string>>* getSendUUIDs();
        State<string>* getNowUUID();
        State<string>* getdutchType();
};