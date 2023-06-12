#pragma once

#include <emscripten/val.h>
#include <string>
#include <memory>
#include <vector>

using namespace emscripten;
using namespace std;

class Style;

class Element
{
    string id;
    val element;
    Style *style;
    std::shared_ptr<Style> style_shared_ptr;
    vector<Element *> children;

    void appendChild(Element *child);

protected:
    static int idCount;

public:
    explicit Element(string tag, Style *style = nullptr, string id = "");
    explicit Element(string tag, shared_ptr<Style> style, string id = "");

    virtual ~Element();

    void appendChildren(Element *child);

    // overloading
    void appendChildren(vector<Element *> children);

    void clearChildren();

    val getElement();

    virtual void update();

    string getId();

    Style &getStyle();
};