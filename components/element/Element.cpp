#include <emscripten/val.h>
#include <string>

#include "../element/Element.h"

using namespace emscripten;
using namespace std;


void Element::appendChild(Element* child) {
    getElement().call<void>("appendChild", child->getElement());
    children.push_back(child);
}

Element::Element(string tag) {
    element = val::global("document").call<val>("createElement", val(tag));
}

Element::~Element() {
    for (Element* child : children) {
        delete child;
    }
    getElement().call<void>("remove");
}

void Element::appendChildren(Element* child) {
    appendChild(child);
}

// overloading
void Element::appendChildren(vector<Element*> children) {
    for (Element* child : children) {
        appendChild(child);
    }
}

val Element::getElement() {
    return element;
}
