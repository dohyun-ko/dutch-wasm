#pragma once

#include <string>
#include "../element/Element.h"
#include <vector>

using namespace std;

template <class T>
class State {
    T val;

    vector<Element*> observers;

    void notify() {
        for (auto observer : observers) {
            observer->update();
        }
    }

public:
    State(T val) : val(val) {}
    ~State() {}

    void attach(Element* observer) {
        observers.push_back(observer);
    }

    void detach(Element* observer) {
        observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
    }

    virtual void setState(T val) {
        this->val = val;
        notify();
    }

    virtual T getValue() {
        return val;
    }
};
