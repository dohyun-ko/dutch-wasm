#include "./Router.h"
#include "../components/element/Element.h"

#include <string>
#include <iostream>
#include <functional>

Router* Router::instance = nullptr;


Router::Router(
    Element* layout,
    const std::unordered_map<string, std::function<Element*()>>& routes,
    const std::string& currentPath
) : layout(layout), routes(routes), currentPath(currentPath) {
    Router::instance = this;

    this->layout->appendChildren(this->routes[currentPath]());
}

Router::~Router() {

}

void Router::navigate(const std::string& path) {

    if (path != "back") {
        delete this->routes[this->currentPath]();
        this->layout->appendChildren(this->routes[path]());
        this->pathHistory.push_back(this->currentPath);
        this->currentPath = path;
    } else {
        if (this->pathHistory.size() == 0) {
            return;
        }
        delete this->routes[this->currentPath]();
        this->layout->appendChildren(this->routes[this->pathHistory.back()]());
        this->currentPath = this->pathHistory.back();
        this->pathHistory.pop_back();
    }
}

Router* Router::getInstance() {
    return Router::instance;
}

Element* Router::getLayout() {
    return this->layout;
}

