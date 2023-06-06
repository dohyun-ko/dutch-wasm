#pragma once
#include <string>
#include <vector>

#include "../../components/state/state.cpp"

class SendDutchState {
    private:
        SendDutchState();
        State<vector<string>>* state;
        static SendDutchState* instance;
    public:
        static SendDutchState* getInstance();
        State<vector<string>>* getState();
};