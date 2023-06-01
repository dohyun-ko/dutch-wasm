#pragma once

#include <string>
#include <unordered_map>
#include "../components/state/State.cpp"
#include "../pages/page/page.h"

class Router {
private:
    std::unordered_map<string, Page*> routes;
    std::string currentPath;
public:
    Router(
        const std::unordered_map<string, Page*>& routes,
        const std::string& currentPath
    );

    ~Router();    

    void navigate(const std::string& path);
};