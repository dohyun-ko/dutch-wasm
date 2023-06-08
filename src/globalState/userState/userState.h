#pragma once
#include <string>

#include "../../core/user/user.h"
#include "../../components/state/State.cpp"

class UserState {
    private:
        UserState();
        State<User>* currentUser;
        State<string>* loginState;
        State<string>* balanceState;
        static UserState* instance;
    public:
        static UserState* getInstance();
        State<User>* getCurrentUser();
        State<string>* getLoginState();
        State<string>* getBalanceState();
};
