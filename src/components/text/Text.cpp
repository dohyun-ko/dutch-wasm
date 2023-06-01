#include <emscripten/val.h>
#include <string>

#include "../element/Element.h"
#include "Text.h"

using namespace emscripten;
using namespace std;

Text::Text(string text) : Element("p") {
    getElement().set("innerHTML", text);
}

Text::~Text() {
    
}