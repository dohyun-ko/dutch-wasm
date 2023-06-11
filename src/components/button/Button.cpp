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
    // text가 없을 수 도 있으므로(children만 있는 버튼)
    if (text == nullptr)
    {
        return;
    }
    text->attach(this);
    getElement().set("innerHTML", text->getValue());
}

Button::Button(std::shared_ptr<State<string>> text, Style *style, string id) : Element("button", style, id), text_shared_ptr(text)
{
    // text가 없을 수 도 있으므로(children만 있는 버튼)
    if (text == nullptr)
    {
        return;
    }
    text->attach(this);
    getElement().set("innerHTML", text->getValue());
}

Button::Button(std::shared_ptr<State<string>> text, std::shared_ptr<Style> style, string id) : Element("button", style, id), text_shared_ptr(text)
{
    // text가 없을 수 도 있으므로(children만 있는 버튼)
    if (text == nullptr)
    {
        return;
    }
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
