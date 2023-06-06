#include <emscripten/val.h>
#include <string>

#include "Input.h"
#include "../style/Style.h"
#include "../state/State.cpp"

Input::Input(State<string>* placeholder, Style* style) : Element("input", style), placeholder(placeholder) {
    placeholder->attach(this);
    getElement().set("placeholder", placeholder->getValue());
}

Input::~Input() {
    placeholder->detach(this);
}

void Input::update() {
    Element::update();
    getElement().set("placeholder", placeholder->getValue());
}
