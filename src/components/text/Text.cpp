#include <emscripten/val.h>
#include <string>

#include "../element/Element.h"
#include "../state/State.cpp"
#include "Text.h"

using namespace emscripten;
using namespace std;

Text::Text(State<string> *text, Style *style) : Element("p", style), text(text)
{
    text->attach(this);
    getElement().set("innerHTML", text->getValue());
}

Text::Text(State<string> *text, std::shared_ptr<Style> style) : Element("p", style), text(text)
{
    text->attach(this);
    getElement().set("innerHTML", text->getValue());
}

Text::Text(std::shared_ptr<State<string>> text, std::shared_ptr<Style> style) : Element("p", style), text_shared_ptr(text)
{
    text_shared_ptr->attach(this);
    getElement().set("innerHTML", text_shared_ptr->getValue());
}

Text::~Text()
{
    if (text != nullptr)
        text->detach(this);
    if (text_shared_ptr != nullptr)
        text_shared_ptr->detach(this);
}

void Text::update()
{
    Element::update();
    if (text != nullptr)
        getElement().set("innerHTML", text->getValue());

    if (text_shared_ptr != nullptr)
        getElement().set("innerHTML", text_shared_ptr->getValue());
}