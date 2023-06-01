#include "./Router.h"
#include "../components/element/Element.h"

#include <string>
#include <iostream>

Router* Router::instance = nullptr;


Router::Router(
    Element* layout,
    const std::unordered_map<string, Element*>& routes,
    const std::string& currentPath
) : layout(layout), routes(routes), currentPath(currentPath) {
    Router::instance = this;

    this->layout->appendChildren(this->routes[currentPath]);
}

Router::~Router() {

}

void Router::navigate(const std::string& path) {
    std::cout << "navigate" << path << endl;
    this->layout->clearChildren();
    this->layout->appendChildren(this->routes[path]);
    this->currentPath = path;
}

Router* Router::getInstance() {
    return Router::instance;
}

Element* Router::getLayout() {
    return this->layout;
}

