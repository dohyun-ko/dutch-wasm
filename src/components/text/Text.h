#pragma once

#include <emscripten/val.h>
#include <string>

#include "../element/Element.h"

using namespace emscripten;
using namespace std;

class Text: public Element {
    public:
        Text(string text);
        virtual ~Text() override;
};