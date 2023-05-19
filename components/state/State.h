#pragma once

#include <string>
#include "../element/Element.h"
#include <vector>

using namespace std;

class State {
    string val = "";

    vector<Element*> observers;

    void notify();

public:
    State(string val);

    void attach(Element* observer);

    void detach(Element* observer);

    void setState(string val);

    string getState();
};
