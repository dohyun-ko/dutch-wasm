#pragma once

#include <emscripten/val.h>
#include <string>
#include <functional>
#include <unordered_map>

#include "../element/Element.h"
#include "../state/State.cpp"


class Button: public Element {
    State<string>* text;
    std::function<void()> onClick;
    static std::unordered_map<string, std::function<void()>> handlers;
    virtual void update() override;

public:
    Button(State<string>* text);

    virtual ~Button() override;

    void setOnClick(std::function<void()> onClick);

    static void clickHandler(emscripten::val e);
};