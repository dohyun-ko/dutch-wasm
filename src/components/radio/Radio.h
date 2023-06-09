#include "../element/Element.h"
#include "../state/State.cpp"
#include <string>

class Radio : public Element
{
    State<std::string> *value;
    State<std::string> *selectedValue;

    Element *radioInput;
    Element *label;

    void update() override;

public:
    Radio(State<std::string> *value = new State<std::string>(""), State<std::string> *selectedValue = new State<std::string>(""), Style *style = nullptr, std::string id = "");

    virtual ~Radio() override;
};