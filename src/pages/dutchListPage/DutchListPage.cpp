#include "DutchListPage.h"
#include "../page/page.h"
#include "../../components/state/State.cpp"
#include "../../components/button/Button.h"
#include "../../components/style/Style.h"
#include "../../components/flex/Flex.h"
#include "../../components/input/Input.h"
#include "../../components/style/Style.h"
#include "../../apiClient/apiClient.h"
#include "../../router/Router.h"
#include "../../components/element/Element.h"
#include <iostream>
#include <functional>
#include <emscripten/bind.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

DutchListPage* DutchListPage::instance = nullptr;

DutchListPage::DutchListPage(): Element("div") {
    this->getStyle()
        .setWidth("100%")
        .setHeight("100%")
        .setDisplay("flex")
        .setFlexDirection("column")
        .setJustifyContent("center")
        .setAlignItems("center");


    Element* dutchListContainer = new Element("div");
    dutchListContainer->getStyle()
        .setWidth("80%")
        .setHeight("80%")
        .setDisplay("grid")
        .setGridTemplateColumns("1fr 1fr 1fr 1fr")
        .setGap("25px");
    
    DutchListPage::appendChildren({dutchListContainer});
}

DutchListPage* DutchListPage::getInstance() {
    if (DutchListPage::instance == nullptr) {
        DutchListPage::instance = new DutchListPage();
    }

    return DutchListPage::instance;

}

DutchListPage::~DutchListPage() {
    DutchListPage::instance = nullptr;
}

EMSCRIPTEN_BINDINGS(Page)
{
}
