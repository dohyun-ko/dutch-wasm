#pragma once
#include <string>
#include <memory>
#include <vector>

#include "../user/user.h"

class Dutch {
    private:
        int targetMoney;
        int sendedMoney;
        std::shared_ptr<User> recieveUser;
        std::vector<std::shared_ptr<User>> sendUsers;
        std::vector<std::shared_ptr<User>> sendedUsers;
    public:
        Dutch(int targetMoney, std::shared_ptr<User> recieveUser, std::vector<std::shared_ptr<User>> sendUsers);
        int getTargetMoney();
        int getSendedMoney();
        std::shared_ptr<User> getRecieveUser();
        std::vector<std::shared_ptr<User>> getSendUsers();
        std::vector<std::shared_ptr<User>> getSendedUsers();
        void setSendedUsers(std::vector<std::shared_ptr<User>> sendedUsers);
};