#include <emscripten/val.h>
#include <emscripten/bind.h>
#include <string>
#include <functional>
#include <unordered_map>

#include "../element/Element.h"
#include "Button.h"
#include "../state/State.h"

#include <iostream>


Button::Button(State* text) : Element("button"), text(text) {
    text->attach(this);
    getElement().set("innerHTML", text->getState());
    getElement().set("style", "width: 200px; background-color: #405cf5; border-radius: 6px; border-width: 0; box-shadow: rgba(50, 50, 93, .1) 0 0 0 1px inset,rgba(50, 50, 93, .1) 0 2px 5px 0,rgba(0, 0, 0, .07) 0 1px 1px 0; height: 44px; outline: none; padding: 0 25px; position: relative; text-align: center; transform: translateZ(0); transition: all .2s,box-shadow .08s ease-in; cursor: pointer; color: #FFFFFF;");
}

Button::~Button() {
    text->detach(this);
}

void Button::update() {
    getElement().set("innerHTML", text->getState());
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