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


Button::Button(State<string>* text) : Element("button"), text(text) {
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

void Button::setOnClick(std::function<void()> onClick) {
    handlers[getId()] = onClick;

    getElement().set("onclick", val::module_property("clickHandler"));
}

void Button::clickHandler(emscripten::val e) {
    // emscripten::val event = emscripten::val::global("event");
    
    try {
        std::cout << "clickHandler" << std::endl;

        emscripten::val target = e["target"];
        std::string id = target["id"].as<std::string>();
        handlers[id]();
    } catch (const std::exception& e) {
        
    }
}

std::unordered_map<string, std::function<void()>> Button::handlers;

EMSCRIPTEN_BINDINGS(Button) {
    emscripten::function("clickHandler", &Button::clickHandler);
}