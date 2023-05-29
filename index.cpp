#include <emscripten/val.h>
#include <emscripten/bind.h>
#include <emscripten/fetch.h>
#include <string>
#include <iostream>
#include <memory>

#include "components/button/Button.h"
#include "components/flex/Flex.h"
#include "components/input/Input.h"
#include "components/state/State.cpp"
#include "components/style/Style.h"
#include "apiClient/apiClient.h"
#include "pages/loginPage/loginPage.h"
#include "pages/signUpPage/signUpPage.h"

using namespace emscripten;
using namespace std;

val getElementById(string id) {
    return val::global("document").call<val>("getElementById", val(id));
}

int main() {
    // val root = getElementById("root");

    // State<string>* webTextState = new State<string>("loading");
    // State<string>* loginText = new State<string>("Login");

    // Flex* container = new Flex("column", "center", "center", "10px");
    // Button* loginButton = new Button(loginText);
    // Button* webButton = new Button(webTextState);
    // Input* usernameInput = new Input("Username");
    // Input* passwordInput = new Input("Password");

    // root.call<void>("appendChild", container->getElement());


    // loginButton->getStyle()
    //     .setWidth("200px")
    //     .setHeight("44px")
    //     .setBackground("#405cf5")
    //     .setBorder("none")
    //     .setBorderRadius("6px")
    //     .setFontSize("1rem")
    //     .setColor("#FFFFFF")
    //     .setPadding("0 25px");

    // webButton->getStyle()
    //     .setWidth("200px")
    //     .setHeight("44px")
    //     .setBackground("#405cf5")
    //     .setBorder("none")
    //     .setBorderRadius("6px")
    //     .setFontSize("1rem")
    //     .setColor("#FFFFFF")
    //     .setPadding("0 25px");

    // container->appendChildren({usernameInput, passwordInput, loginButton, webButton});

    // loginButton->setOnClick([&]() {
    //     loginText->setState("Logout");
    // });
    val root = getElementById("root");

    LoginPage* loginPage = new LoginPage(root);
    loginPage->render();

    emscripten_sleep(3000);

    loginPage->remove();

    SignUpPage* signUpPage = new SignUpPage(root);
    signUpPage->render();
}