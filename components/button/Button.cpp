#include <emscripten/val.h>
#include <string>

#include "../element/Element.h"
#include "Button.h"

using namespace emscripten;
using namespace std;


Button::Button(string text) : Element("button"), text(text) {
    getElement().set("innerHTML", text);
    getElement().set("style", "width: 200px; background-color: #405cf5; border-radius: 6px; border-width: 0; box-shadow: rgba(50, 50, 93, .1) 0 0 0 1px inset,rgba(50, 50, 93, .1) 0 2px 5px 0,rgba(0, 0, 0, .07) 0 1px 1px 0; height: 44px; outline: none; padding: 0 25px; position: relative; text-align: center; transform: translateZ(0); transition: all .2s,box-shadow .08s ease-in; cursor: pointer; color: #FFFFFF;");
}

Button::~Button() {}

void Button::changeText(string text) {
    getElement().set("innerHTML", text);
}

void Button::setOnClick(void (*callback)()) {
    getElement().set("onclick", callback);
}
