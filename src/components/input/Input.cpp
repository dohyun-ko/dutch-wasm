#include <emscripten/val.h>
#include <string>

#include "Input.h"

Input::Input(string placeholder): Element("input"), placeholder(placeholder) {
    getElement().set("placeholder", placeholder);
    getElement().set("style", "width: 148px; border: 1px solid black; border-radius: 6px; height: 44px; outline: none; padding: 0 25px; position: relative; text-align: center; transform: translateZ(0); transition: all .2s,box-shadow .08s ease-in; cursor: pointer; color: #FFFFFF;");
}

Input::~Input() {
    
}