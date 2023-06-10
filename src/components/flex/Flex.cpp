#include <emscripten/val.h>
#include <string>

#include "../element/Element.h"
#include "Flex.h"
#include "../style/Style.h"

using namespace emscripten;
using namespace std;

Flex::Flex(
    string direction,
    string justifyContent,
    string alignItems,
    string gap) : Element("div", new Style())
{
    this->getStyle()
        .setDisplay("flex")
        .setFlexDirection(direction)
        .setJustifyContent(justifyContent)
        .setAlignItems(alignItems)
        .setGap(gap);
}

Flex::~Flex()
{
}