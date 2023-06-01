#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include "../components/state/State.cpp"
#include "../pages/page/page.h"
#include "../components/element/Element.h"

class Router {
private:
    static Router* instance;
    std::unordered_map<string, std::function<Element*()>> routes;
    std::string currentPath;
    std::vector<string> pathHistory;
    Element* layout;
public:
    Router(
        Element* layout,
        const std::unordered_map<string, std::function<Element*()>>& routes,
        const std::string& currentPath
    );

    ~Router();    

    static Router* getInstance();

    void navigate(const std::string& path);

    Element* getLayout();
};