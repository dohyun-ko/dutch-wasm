#pragma once

#include <emscripten/val.h>
#include <string>

using namespace emscripten;
using namespace std;

class Element {
    val element;
    vector<Element*> children;

    void appendChild(Element* child);


public:
    Element(string tag);

    void appendChildren(Element* child);

    // overloading
    void appendChildren(vector<Element*> children);

    val getElement();
};