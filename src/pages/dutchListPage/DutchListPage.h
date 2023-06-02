#pragma once

#include <emscripten/bind.h>
#include "../page/page.h"
#include "../../components/state/State.cpp"
#include "../../components/button/Button.h"
#include "../../components/flex/Flex.h"
#include "../../components/input/Input.h"

class DutchListPage : public Element
{
    static DutchListPage* instance;

    DutchListPage();

    Element* dutchListContainer;

public:
    ~DutchListPage();

    static DutchListPage* getInstance();
};
