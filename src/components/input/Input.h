#pragma once

#include <emscripten/val.h>
#include <string>

#include "../element/Element.h"
#include "../state/State.cpp"
#include "../style/Style.h"

using namespace emscripten;
using namespace std;

class Input : public Element {
    State<string>* placeholder;
    
    void update() override;
public:
    Input(State<string>* placeholder = new State<string>(""), Style* style = nullptr);
    
    virtual ~Input() override;
};
