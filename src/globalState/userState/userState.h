#pragma once
#include <string>

#include "../../core/user/user.h"
#include "../../components/state/state.cpp"

class UserState {
    private:
        UserState();
        State<User>* state;
        static UserState* instance;
    public:
        static UserState* getInstance();
        State<User>* getState();
};
