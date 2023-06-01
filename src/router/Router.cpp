#include "./Router.h"

#include <string>


Router::Router(
    const std::unordered_map<string, Page*>& routes,
    const std::string& currentPath
) : routes(routes), currentPath(currentPath) {
    this->routes[currentPath]->render();
}

Router::~Router() {

}

void Router::navigate(const std::string& path) {
    this->routes[currentPath]->remove();
    this->routes[path]->render();
    this->currentPath = path;
}