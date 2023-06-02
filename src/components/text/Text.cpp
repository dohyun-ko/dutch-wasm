#include <emscripten/val.h>
#include <string>

#include "../element/Element.h"
#include "../state/State.cpp"
#include "Text.h"

using namespace emscripten;
using namespace std;

Text::Text(State<string>* text, Style* style) : Element("p", style), text(text) {
    text->attach(this);
    getElement().set("innerHTML", text->getValue());
}

Text::~Text() {
    
}

void Text::update() {
    Element::update();
    getElement().set("innerHTML", text->getValue());
}