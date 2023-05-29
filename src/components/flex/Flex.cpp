#include <emscripten/val.h>
#include <string>

#include "../element/Element.h"
#include "Flex.h"

using namespace emscripten;
using namespace std;

Flex::Flex(
    string direction,
    string justifyContent,
    string alignItems,
    string gap
) : Element("div") {
    getElement().set("style", "display: flex; flex-direction: " + direction + "; justify-content: " + justifyContent + "; align-items: " + alignItems + "; gap: " + gap + ";");
}

Flex::~Flex() {
    
}