#pragma once
#include <emscripten/val.h>
#include "../../components/element/Element.h"

using namespace emscripten;

class Page : public Element {
    public:
        Page();
        virtual void render() = 0;
        virtual void remove() = 0;
    
};