#pragma once
#include <string>
#include <memory>
#include <vector>

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
};