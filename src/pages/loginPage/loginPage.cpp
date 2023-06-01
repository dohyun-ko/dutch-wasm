#include "loginPage.h"
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

State<string> *LoginPage::loginTextState = new State<string>("Login");

LoginPage::LoginPage(): Element("div") {
    signUpTextState = new State<string>("Sign Up");
    backwardTextState = new State<string>("Back");

    buttonStyle = new Style();
    buttonStyle
        ->setWidth("200px")
        .setHeight("44px")
        .setBackground("#405cf5")
        .setBorder("none")
        .setBorderRadius("6px")
        .setFontSize("1rem")
        .setColor("#FFFFFF")
        .setPadding("0 25px");

    container = new Flex("column", "center", "center", "10px");
    loginButton = new Button(loginTextState, buttonStyle);
    signUpButton = new Button(signUpTextState, buttonStyle);
    usernameInput = new Input(new State<string>("Username"));
    passwordInput = new Input(new State<string>("Password"));

    usernameInput->getStyle()
        .setWidth("148px")
        .setHeight("44px")
        .setBorder("1px solid black")
        .setBorderRadius("6px")
        .setPadding("0 25px");

    passwordInput->getStyle()
        .setWidth("148px")
        .setHeight("44px")
        .setBorder("1px solid black")
        .setBorderRadius("6px")
        .setPadding("0 25px");


    container->appendChildren({usernameInput, passwordInput, loginButton, signUpButton});

    loginButton->getElement().set("onclick", emscripten::val::module_property("LoginPage.LoginButtonHander"));
    signUpButton->getElement().set("onclick", emscripten::val::module_property("LoginPage.SignUpButtonHander"));

    LoginPage::appendChildren(container);
}


void LoginPage::LoginButtonHander(emscripten::val e) {
    std::cout << "LoginPage::LoginButtonHander()" << std::endl;
    loginTextState->setState("Logging in...");
    ApiClient apiClient();
}

void LoginPage::SignUpButtonHander(emscripten::val e) {
    std::cout << "LoginPage::SignUpButtonHander()" << std::endl;
    Router* router = Router::getInstance();
    std::cout << "router: " << router << std::endl;
    router->navigate("/signUp"); // TODO: maybe it's better to change navigate to a static method
    std::cout << "router->navigate" << std::endl;
}

LoginPage::~LoginPage() {
    delete loginTextState;
    delete signUpTextState;
    delete container;
    delete loginButton;
    delete signUpButton;
    delete usernameInput;
    delete passwordInput;
}

EMSCRIPTEN_BINDINGS(Page){
    emscripten::function("LoginPage.LoginButtonHander", &LoginPage::LoginButtonHander);
    emscripten::function("LoginPage.SignUpButtonHander", &LoginPage::SignUpButtonHander);
}
