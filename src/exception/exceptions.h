#pragma once
#include <exception>
#include <string>

class TimeoutExcetption : public std::exception {
    public:
        const char * what () const noexcept{
            return "Timeout";
        }
};

class NetworkException : public std::exception {
    int code;
    public:
        NetworkException(int code) {
            this->code = code;
        }
        const char * what () const noexcept{
            std::string message = "Network Error " + std::to_string(this->code);
            return message.c_str();
        }
};