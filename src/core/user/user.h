#pragma once
#include <string>
#include <memory>
#include <vector>

#include "../dutch/dutch.h"

class User {
    private:
        std::string UUID;
        std::string username;
        std::string email;
    public:
        User(std::string UUID, std::string username, std::string email);
        std::string getUUID();
        std::string getUsername();
        std::string getEmail();
        std::shared_ptr<Dutch> makeDutch(int targetMoney, std::vector<std::shared_ptr<User>> sendUsers);
};