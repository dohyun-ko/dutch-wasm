#pragma once
#include <emscripten/val.h>

using namespace emscripten;

class Page {
    protected:
        val root;
    public:
        Page(val root);
        virtual void render() = 0;
};