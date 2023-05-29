#include <emscripten/val.h>

#include "page.h"

using namespace emscripten;;

Page::Page(val* root) {
    this->root = root;
}