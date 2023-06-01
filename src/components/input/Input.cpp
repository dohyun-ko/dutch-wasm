#include <emscripten/val.h>
#include <string>

#include "Input.h"
#include "../style/Style.h"
#include "../state/State.cpp"

Input::Input(State<string>* placeholder) : Element("input"), placeholder(placeholder) {
    placeholder->attach(this);
    getElement().set("placeholder", placeholder->getValue());
}

Input::~Input() {
    placeholder->detach(this);
}

void Input::update() {
    getElement().set("placeholder", placeholder->getValue());
    getElement().set("style", getStyle().getCssString());
}
