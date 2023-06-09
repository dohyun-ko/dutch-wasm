#include "Radio.h"
#include "../element/Element.h"

Radio::Radio(State<std::string> *value, State<std::string> *selectedValue, Style *style, std::string id) : Element("div", style), value(value), selectedValue(selectedValue)
{
    id = id.length() > 0 ? id : "radio-" + to_string(idCount++);

    value->attach(this);
    selectedValue->attach(this);

    this->radioInput = new Element("input", nullptr, id);
    this->label = new Element("label", nullptr, id + "-label");

    this->radioInput->getElement().set("type", "radio");
    this->radioInput->getElement().set("name", "radio");
    this->radioInput->getElement().set("value", value->getValue());
    this->radioInput->getElement().set("checked", value->getValue() == selectedValue->getValue());

    this->label->getElement().set("for", id);
    this->label->getElement().set("innerHTML", value->getValue());

    this->appendChildren({this->radioInput, this->label});
}

Radio::~Radio()
{
    delete this->radioInput;
    delete this->label;

    value->detach(this);
    selectedValue->detach(this);
}

void Radio::update()
{
    Element::update();
    this->radioInput->getElement().set("value", value->getValue());
    this->radioInput->getElement().set("checked", value->getValue() == selectedValue->getValue());

    this->label->getElement().set("innerHTML", value->getValue());
}