#include <emscripten/val.h>
#include <emscripten/bind.h>
#include <string>
#include <functional>
#include <unordered_map>

#include "../element/Element.h"
#include "Button.h"
#include "../state/State.cpp"
#include "../style/Style.h"

#include <iostream>


Button::Button(State<string>* text, Style* style) : Element("button", style), text(text) {
    text->attach(this);
    getElement().set("innerHTML", text->getValue());
}

Button::~Button() {
    text->detach(this);
}

void Button::update() {
    getElement().set("innerHTML", text->getValue());
    getElement().set("style", getStyle().getCssString());
}

void Button::setOnClick() {
    std::cout << "setOnClick" << endl;
    getElement().set("onclick", emscripten::val::module_property("handleClick"));
}

void handleClick(emscripten::val event) {
    std::cout << "clicked" << endl;
}

EMSCRIPTEN_BINDINGS(components) {
    emscripten::function("handleClick", &handleClick);
}