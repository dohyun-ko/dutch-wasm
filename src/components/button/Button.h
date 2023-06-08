#pragma once

#include <emscripten/val.h>
#include <string>
#include <functional>
#include <unordered_map>

#include "../element/Element.h"
#include "../state/State.cpp"

class Button : public Element
{
    State<string> *text;
    std::function<void()> onClick;
    virtual void update() override;
    friend void handleClick(emscripten::val event);

public:
    Button(State<string> *text, Style *style = nullptr, string id = "");

    virtual ~Button() override;

    void setOnClick();
};