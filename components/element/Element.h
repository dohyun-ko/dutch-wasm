#pragma once

#include <emscripten/val.h>
#include <string>

using namespace emscripten;
using namespace std;

class Element {
    static int idCount;
    string id;
    val element;
    vector<Element*> children;

    void appendChild(Element* child);

public:
    Element(string tag);
    
    virtual ~Element();

    void appendChildren(Element* child);

    // overloading
    void appendChildren(vector<Element*> children);

    val getElement();

    virtual void update();

    string getId();
};