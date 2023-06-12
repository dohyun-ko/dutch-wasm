#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <memory>
#include "../components/state/State.cpp"
#include "../components/element/Element.h"

class Router
{
private:
    static Router *instance;
    std::unordered_map<string, std::function<Element *()>> routes;
    std::string currentPath;
    std::vector<string> pathHistory;
    std::shared_ptr<Element> layout;

public:
    Router(
        std::shared_ptr<
            Element>
            layout,
        const std::unordered_map<string, std::function<Element *()>> &routes,
        const std::string &currentPath);

    ~Router();

    static Router *getInstance();

    void navigate(const std::string &path);

    std::shared_ptr<Element> getLayout();
};