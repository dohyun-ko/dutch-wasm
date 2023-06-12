#pragma once

#include <emscripten/val.h>
#include <string>

#include "../element/Element.h"
#include "../state/State.cpp"

using namespace emscripten;

class Text : public Element
{
    State<string> *text;
    std::shared_ptr<State<string>> text_shared_ptr;

    virtual void update() override;

public:
    Text(State<string> *text, Style *style = nullptr);
    Text(State<string> *text, std::shared_ptr<Style> style);
    Text(std::shared_ptr<State<string>> text, std::shared_ptr<Style> style = nullptr);
    virtual ~Text() override;
};