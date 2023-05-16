#include <emscripten/val.h>
#include <string>

#include "../element/Element.h"

using namespace emscripten;
using namespace std;

int Element::idCount = 0;

Element::Element(string tag) {
    element = val::global("document").call<val>("createElement", val(tag));
    string newId = "element" + to_string(idCount++);
    element.set("id", newId);
    id = newId;
}

Element::~Element() {
    for (Element* child : children) {
        delete child;
    }
    getElement().call<void>("remove");
}

void Element::appendChild(Element* child) {
    getElement().call<void>("appendChild", child->getElement());
    children.push_back(child);
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

void Element::update() {
    // do nothing
}

string Element::getId() {
    return id;
}