#pragma once

#include <emscripten/val.h>
#include <string>

#include "../element/Element.h"
#include "../state/State.cpp"

using namespace emscripten;

class Text: public Element {
    State<string>* text;

    public:
        Text(State<string>* text, Style* style = nullptr);
        virtual ~Text() override;

        virtual void update() override;
};