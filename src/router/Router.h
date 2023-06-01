#pragma once

#include <string>
#include <unordered_map>
#include "../components/state/State.cpp"
#include "../pages/page/page.h"
#include "../components/element/Element.h"

class Router {
private:
    static Router* instance;
    std::unordered_map<string, Element*> routes;
    std::string currentPath;
    Element* layout;
public:
    Router(
        Element* layout,
        const std::unordered_map<string, Element*>& routes,
        const std::string& currentPath
    );

    ~Router();    

    static Router* getInstance();

    void navigate(const std::string& path);

    Element* getLayout();
};