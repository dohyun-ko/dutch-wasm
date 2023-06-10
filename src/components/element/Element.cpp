#include <emscripten/val.h>
#include <string>
#include <iostream>

#include "../element/Element.h"
#include "../style/Style.h"

using namespace emscripten;
using namespace std;

int Element::idCount = 0;

Element::Element(string tag, Style *style, string id) : style(style)
{
    element = val::global("document").call<val>("createElement", val(tag));
    string newId = id.length() > 0 ? id : tag + to_string(idCount++);
    element.set("id", newId);
    id = newId;
    if (style != nullptr)
    {
        style->attach(this);
        getElement().set("style", style->getCssString());
    }
}

Element::~Element()
{
    std::cout << "delete id: " << id << std::endl;
    // for (Element* child : children) {
    //     delete child;
    // } // TODO : memory leak
    getElement().call<void>("remove");
}

void Element::appendChild(Element *child)
{
    getElement().call<void>("appendChild", child->getElement());
    children.push_back(child);
}

void Element::appendChildren(Element *child)
{
    appendChild(child);
}

// overloading
void Element::appendChildren(vector<Element *> children)
{
    for (Element *child : children)
    {
        appendChild(child);
    }
}

void Element::clearChildren()
{
    for (Element *child : children)
    {
        delete child;
    }

    // children.clear(); // TODO: memory leak
}

val Element::getElement()
{
    return element;
}

void Element::update()
{
    getElement().set("style", getStyle().getCssString());
}

string Element::getId()
{
    return id;
}

Style &Element::getStyle()
{
    if (style == nullptr)
    {
        style = new Style(); // TODO: memory leak
        style->attach(this);
    }
    return *style;
}