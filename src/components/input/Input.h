#pragma once

#include <emscripten/val.h>
#include <string>

#include "../element/Element.h"
#include "../state/State.cpp"

using namespace emscripten;
using namespace std;

class Input : public Element {
    State<string>* placeholder;
    
    void update() override;
public:
    Input(State<string>* placeholder = new State<string>(""));
    
    virtual ~Input() override;
};
