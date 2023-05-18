#include <string>
#include <vector>
#include "../element/Element.h"
#include "State.h"

using namespace std;

void State::notify() {
    for (auto observer : observers) {
        observer->update();
    }
}

State::State(string val) : val(val) {}

void State::attach(Element* observer) {
    observers.push_back(observer);
}

void State::detach(Element* observer) {
    observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
}

void State::setState(string val) {
    this->val = val;
    notify();
}

string State::getState() {
    return val;
}
