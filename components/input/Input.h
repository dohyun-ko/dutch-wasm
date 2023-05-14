#pragma once

#include <emscripten/val.h>
#include <string>

#include "../element/Element.h"

using namespace emscripten;
using namespace std;

class Input : public Element {
    string placeholder;
public:
    Input(string placeholder = "");
};
