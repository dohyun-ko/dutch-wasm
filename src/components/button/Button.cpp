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

Button::Button(State<string> *text, Style *style, string id) : Element("button", style, id), text(text)
{
    text->attach(this);
    getElement().set("innerHTML", text->getValue());
}

Button::~Button()
{
    text->detach(this);
}

void Button::update()
{
    Element::update();
    getElement().set("innerHTML", text->getValue());
}

void Button::setOnClick()
{
    getElement().set("onclick", emscripten::val::module_property("handleClick"));
}
