#pragma once

#include <emscripten/val.h>
#include <string>

#include "../element/Element.h"

using namespace emscripten;
using namespace std;

class Button: public Element {
    string text;
    void (*onClick)();

public:
    Button(string text);
    
    void changeText(string text);
    void setOnClick(void (*callback)());
};