#include <emscripten/val.h>
#include <emscripten/bind.h>
#include <emscripten/fetch.h>
#include <string>
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>

#include "components/button/Button.h"
#include "components/flex/Flex.h"
#include "components/input/Input.h"
#include "components/state/State.cpp"
#include "components/style/Style.h"
#include "pages/loginPage/loginPage.h"
#include "pages/signUpPage/signUpPage.h"
#include "pages/sendPage/sendPage.h"
#include "pages/sendDetailPage/sendDetailPage.h"
#include "pages/receivePage/receivePage.h"
#include "pages/mainPage/mainPage.h"
#include "router/Router.h"

using namespace emscripten;
using json = nlohmann::json;

val getElementById(std::string id)
{
    return val::global("document").call<val>("getElementById", val(id));
}

static void backButtonHander(emscripten::val e)
{
    Router::getInstance()->navigate("back");
}

EMSCRIPTEN_BINDINGS(layout)
{
    emscripten::function("layout.backButtonHander", &backButtonHander);
}

int main()
{
    val root = getElementById("root");

    Element *layout = new Element("div");

    layout->getStyle()
        .setPosition("relative")
        .setDisplay("flex")
        .setFlexDirection("column")
        .setAlignItems("center");

    Element *header = new Element("div");
    header->getStyle()
        .setPosition("absolute")
        .setTop("0")
        .setLeft("0")
        .setDisplay("flex")
        .setAlignItems("center")
        .setWidth("100%")
        .setHeight("80px");

    Element *body = new Element("div");
    body->getStyle()
        .setDisplay("flex")
        .setFlexDirection("column")
        .setAlignItems("center")
        .setJustifyContent("center")
        .setWidth("100%")
        .setHeight("calc(100vh)")
        .setBackground(Style::secondary);

    Button *backButton = new Button(new State<string>("⬅️"));
    backButton->getStyle()
        .setBorder("none")
        .setBackground("transparent")
        .setFontSize("2rem")
        .setCursor("pointer");

    backButton->getElement().set("onclick", emscripten::val::module_property("layout.backButtonHander"));
    header->appendChildren(backButton);
    layout->appendChildren({header, body});

    root.call<void>("appendChild", layout->getElement());

    Router router(
        body,
        {
            {"/login", []()
             { return LoginPage::getInstance(); }},
            {"/signUp", []()
             { return SignUpPage::getInstance(); }},
            {"/main", []()
             { return MainPage::getInstance(); }},
            {"/send", []()
             { return SendPage::getInstance(); }},
            {"/sendDetail", []()
             { return SendDetailPage::getInstance(); }},
            {"/receive", []()
             { return ReceivePage::getInstance(); }},
        },
        "/main");

    while (true)
    {
        emscripten_sleep(100);
    }

    // emscripten_set_main_loop() // TODO: use this instead of sleep

    // router.navigate("/signUp");

    // SignUpPage* signUpPage = new SignUpPage(root);
    // signUpPage->render();

    // emscripten_sleep(3000);

    // signUpPage->remove();

    // mainPage->render();
}
